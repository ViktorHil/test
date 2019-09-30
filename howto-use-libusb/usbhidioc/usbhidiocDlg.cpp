// usbhidiocDlg.cpp : implementation file
/*
Project: usbhidioc.cpp
Version: 2.0
Date: 12/20/00
by Jan Axelson (jan@lvr.com)

Назначение: демонстрация USB коммуникации HID-class device с использованием overlapped I/O.

Описание: 
	Находится подсоединенное HID-class device, которое соответствует заданным vendor & product IDs.
	Получение device capabilities.
	Посылается 2 байта в устройство с использованием Input reports.
	Принимаются 2 байта от устройства с использованием Output reports. 
	List box отображает лог активности.
	List box Bytes Received отображает самые новые принятые байты репорта.
	Combo-боксы разрешают пользователю выбрать байты для отправки.
	Чекбокс "autoincrement" включает автоинкремент количества отсылаемых байт в каждом репорте.
	Щелчок на кнопке "Once" запускает обмен одним набором репортов.
	Щелчок на кнопке "Continuous" запускает обмен репортами периодически каждые 5 секунд).
	
Приложение было создано в Visual C++ 6 в диалоге AppWizard на основе шаблона "dialog-based application".

Соответствующее firmware и другие примеры доступны на www.lvr.com.

Благодарю за помощь Usenet и отличный архив www.deja.com/usenet, которые помогли мне 
с Visual C++ в этом проекте. Другие источники, которые я использовал - www.natsemi.com
с примером HID application и John Hyde's terminal program на www.usb-by-example.com.

Основное изменение по сравнению с предыдущей версией - использование overlapped I/O.

Посылайте комментарии, вопросы, сообщения об ошибках и проч. на jan@lvr.com.

[Об overlapped I/O]

Чтение HID input reports осуществляется с API функцией ReadFile. 
Non-overlapped ReadFile является блокирующим вызовом. Если устройство не возвращает 
ожидаемое количество данных, приложение зависает, так как ожидание происходит бесконечно.

С использование overlapped I/O вызов ReadFile происходит с немедленным возвратом. Приложение 
запускает WaitForSingleObject, которое возвращаетсч либо когда данные пришли, либо когда 
произощел указанный таймаут.

Эта программа была протестирована в Windows 98 SE и Windows 2000.
*/

#include "stdafx.h"

#include "usbhidioc.h"
#include "usbhidiocDlg.h"

#include <wtypes.h>
#include <initguid.h>

#define MAX_LOADSTRING 256

extern "C" {
#include "hidsdi.h"
#include <setupapi.h>
}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//function prototypes
bool FindTheHID();
void DisplayCurrentTime();
void DisplayData(CString cstrDataToDisplay);
void DisplayInputReport();
void DisplayLastError(CString Operation);
void DisplayReceivedData(char ReceivedByte);
void GetDeviceCapabilities();
void PrepareForOverlappedTransfer();
void ReadAndWriteToDevice();
void ReadReport();
void ScrollToBottomOfListBox(USHORT Index);
void WriteReport();

extern void WINAPI HIDIOCompletionRoutine(DWORD, DWORD, LPOVERLAPPED);

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbhidiocDlg dialog

CUsbhidiocDlg::CUsbhidiocDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUsbhidiocDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUsbhidiocDlg)
	m_AutoIncrement = FALSE;
	m_ResultsString = _T("");
	m_strBytesReceived = _T("");
	m_strByteToSend0 = _T("");
	m_strByteToSend1 = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


//Application global variables 
	DWORD			ActualBytesRead;
	DWORD			BytesRead;
	HIDP_CAPS		Capabilities;
	DWORD			cbBytesRead;
	PSP_DEVICE_INTERFACE_DETAIL_DATA	detailData;
	bool			DeviceDetected;
	HANDLE			DeviceHandle;
	DWORD			dwError;
	HANDLE			hEventObject;
	HANDLE			hDevInfo;
	GUID			HidGuid;
	OVERLAPPED		HIDOverlapped;
	char			InputReport[3];
	ULONG			Length;
	LPOVERLAPPED	lpOverLap;
	DWORD			NumberOfBytesRead;
	HANDLE			ReadHandle;
	ULONG			Required;
	CString			ValueToDisplay;

void CUsbhidiocDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsbhidiocDlg)
	DDX_Control(pDX, IDC_Continuous, m_Continuous);
	DDX_Control(pDX, IDC_AutoIncrement, m_cbutAutoIncrement);
	DDX_Control(pDX, IDC_cboByteToSend1, m_cboByteToSend1);
	DDX_Control(pDX, IDC_cboByteToSend0, m_cboByteToSend0);
	DDX_Control(pDX, IDC_lstBytesReceived, m_BytesReceived);
	DDX_Control(pDX, IDC_LIST2, m_ResultsList);
	DDX_Control(pDX, IDC_Once, m_Once);
	DDX_Check(pDX, IDC_AutoIncrement, m_AutoIncrement);
	DDX_LBString(pDX, IDC_LIST2, m_ResultsString);
	DDX_LBString(pDX, IDC_lstBytesReceived, m_strBytesReceived);
	DDX_CBString(pDX, IDC_cboByteToSend0, m_strByteToSend0);
	DDX_CBString(pDX, IDC_cboByteToSend1, m_strByteToSend1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUsbhidiocDlg, CDialog)
	//{{AFX_MSG_MAP(CUsbhidiocDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Once, OnOnce)
	ON_EN_CHANGE(IDC_Results, OnChangeResults)
	ON_BN_CLICKED(IDC_Continuous, OnContinuous)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbhidiocDlg message handlers

BOOL CUsbhidiocDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Начало моих определений
	int		ByteToSend =0;
	CString	strByteToSend = "";
	CString	strComboBoxText="";
	//Конец моих определений

	// Добавление в системное меню пункта "About...".

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	/*
	Мой код начинается здесь. Все, что нужно выполнить при старте
	приложения, происходит здесь.
	*/

	//Заполняем combo boxes величинами от 00 до FF.
	DeviceDetected=FALSE;

	for (ByteToSend=0; ByteToSend < 256; ByteToSend++)
	{
		//Отображаем значения как 2-digit Hex value.
		strByteToSend.Format("%.2X",ByteToSend);
		m_cboByteToSend0.AddString(strByteToSend);
		m_cboByteToSend1.AddString(strByteToSend);	
	}

	//Выбор значения по умолчанию в combo boxes.
	m_cboByteToSend0.SetCurSel(0);
	m_cboByteToSend1.SetCurSel(128);

	//Ставим галочку в autoincrement check box.
	m_cbutAutoIncrement.SetCheck(1);

	//Устанавливаем надпись на кнопке "Continous".
	m_Continuous.SetWindowText("Continuous");
	//конец моего кода

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUsbhidiocDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CUsbhidiocDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUsbhidiocDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*
My routines (routines specific to this application) start here.
*/

void CUsbhidiocDlg::OnOnce() 
{
	//Click the Once button to read and write one pair of reports.
	ReadAndWriteToDevice();
}

void CUsbhidiocDlg::OnContinuous() 
{
	//Щелчок на кнопке "Continuous" запускает или останавливает
	// запросы и отправки периодических репортов.
	CString Caption;

	//Определяем, в каком состоянии кнопка - от этого 
	// зависят дальнейшие действия.
	m_Continuous.GetWindowText(Caption);
	if (Caption == "Continuous")
	{
		//Разрешение периодических обменов репортами.
		//Изменяем надпись на кнопке.
		m_Continuous.SetWindowText("Stop Continuous");
		//Стартуем чтение и запись пары репортов.
		ReadAndWriteToDevice();
		//Включаем таймер для периодической отправки репортов.
		//Второй параметр - число милисекунд между report requests.
		SetTimer(ID_CLOCK_TIMER, 5000, NULL);
	}
	else
	{
		//Остановка периодического обмена репортами.
		//Изменяем надпись на кнопке.
		m_Continuous.SetWindowText("Continuous");
		//Отключаем таймер.
		KillTimer(ID_CLOCK_TIMER);
	}
}

void CUsbhidiocDlg::OnClose() 
{
	//Anything that needs to occur on closing the application goes here.
	//Free any resources used by previous API calls and still allocated.

	//Close open handles.
	CloseHandle(DeviceHandle);
	DisplayLastError("CloseHandle(DeviceHandle)");

	CloseHandle(ReadHandle);
	DisplayLastError("CloseHandle(ReadHandle)");

	CDialog::OnClose();
}

bool CUsbhidiocDlg::FindTheHID()
{
	//Использование серии вызовов API для нахождения HID с подходящими Vendor и Product ID.

	HIDD_ATTRIBUTES						Attributes;
	SP_DEVICE_INTERFACE_DATA			devInfoData;
	bool								LastDevice = FALSE;
	int									MemberIndex = 0;
	bool								MyDeviceDetected = FALSE; 
	LONG								Result;

	//Тут указаны требуемые Vendor ID и Product ID.
	//Используются Lakeview Research's Vendor ID.
	//const unsigned int VendorID = 0x0925;
	//const unsigned int ProductID = 0x1234;
	//А это я переделал под obdev-параметры (используются в примере firmware hid-custom-rq):
	const unsigned int VendorID = 0x16c0;
	const unsigned int ProductID = 0x05df;

	Length = 0;
	detailData = NULL;
	DeviceHandle=NULL;

	/*
	Функция API: HidD_GetHidGuid
	Получение GUID для всех HID-ов в системе.
	Returns: GUID в переменной HidGuid.
	*/
	HidD_GetHidGuid(&HidGuid);	
	
	/*
	Функция API: SetupDiGetClassDevs
	Returns: handle к device information set для всех инсталлированных devices.
	Requires: GUID, возвращенный GetHidGuid.
	*/
	hDevInfo=SetupDiGetClassDevs 
		(&HidGuid, 
		NULL, 
		NULL, 
		DIGCF_PRESENT|DIGCF_INTERFACEDEVICE);
		
	devInfoData.cbSize = sizeof(devInfoData);

	//Просмотр всех доступных устройств, чтобы найти из них нужное. 
	//Выход, когда найдено требуемое устройство, либо когда все устройства 
	// просканированы, но нужное не найдено.
	MemberIndex = 0;
	LastDevice = FALSE;

	do
	{
		MyDeviceDetected=FALSE;
		
		/*
		Функция API: SetupDiEnumDeviceInterfaces
		На выходе devInfoData содержит хендл к структуре 
		SP_DEVICE_INTERFACE_DATA для детектированного устройства.
		Требует:
		hDevInfo, полученный SetupDiGetClassDevs, HidGuid полученный от GetHidGuid,
		индекс для указания устройства.
		*/
		Result=SetupDiEnumDeviceInterfaces 
			(hDevInfo, 
			0, 
			&HidGuid, 
			MemberIndex, 
			&devInfoData);

		if (Result != 0)
		{
			//Устройство продетектировано, получим больше информации о нем.
			/*
			Функция API: SetupDiGetDeviceInterfaceDetail
			Возвращает: структуру SP_DEVICE_INTERFACE_DETAIL_DATA,
			содержащую информацию об устройстве.
			Для получения информации эта функция вызывается дважды.
			В первый раз получаем размер структуры в переменной Length.
			Второй раз получаем указатель на данные в devInfoData.
			Требует:
			devInfoData, полученную вызовом SetupDiGetClassDevs,
			структуру SP_DEVICE_INTERFACE_DATA, полученную вызовом SetupDiEnumDeviceInterfaces.
			
			Последний параметр - необязательный указатель на структуру SP_DEV_INFO_DATA.
			Это приложение не использует эту структуру.			
			Если запрашивается структура, то установите 
			MyDeviceInfoData.cbSize = length devInfoData, и передайте адрес структуры.
			*/
			
			//Получаем длину (Length).
			//Вызов вернет ошибку "buffer too small", которую можно проигнорировать.
			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				NULL, 
				0, 
				&Length, 
				NULL);

			//Выделяем память для структуры hDevInfo, используя полученную длину.
			detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);
			
			//Set cbSize in the detailData structure.
			detailData -> cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			//Вызываем функцию снова, в этот раз с правильной длиной буфера.
			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				detailData, 
				Length, 
				&Required, 
				NULL);

			//Открываем handle к устройству.

			/*
			Функция API: CreateFile
			Возврат: handle, которое позволяет читать и записывать устройство.
			Требует:
			DevicePath в структуре detailData, котоый был получен вызовом
			SetupDiGetDeviceInterfaceDetail.
			*/
			DeviceHandle=CreateFile 
				(detailData->DevicePath, 
				GENERIC_READ|GENERIC_WRITE, 
				FILE_SHARE_READ|FILE_SHARE_WRITE, 
				(LPSECURITY_ATTRIBUTES)NULL,
				OPEN_EXISTING, 
				0, 
				NULL);

			DisplayLastError("CreateFile: ");

			/*
			Функция API: HidD_GetAttributes
			Запрашивает информацию об устройстве.
			Требует: handle, полученное от CreateFile.
			Возвращает: структуру HIDD_ATTRIBUTES, содержащую 
			Vendor ID, Product ID, Product Version Number.
			Эта инфа используется для определения - то ли это устройство,
			что мы ищем.
			*/

			//Установим Size в количество байт в структуре.
			Attributes.Size = sizeof(Attributes);

			Result = HidD_GetAttributes 
				(DeviceHandle, 
				&Attributes);
			
			DisplayLastError("HidD_GetAttributes: ");
			
			//Устройтсво - то, которое нужно?
			MyDeviceDetected = FALSE;
			if (Attributes.VendorID == VendorID)
			{
				if (Attributes.ProductID == ProductID)
				{
					//Совпадают и Product и Vendor ID.
					MyDeviceDetected = TRUE;
					DisplayData("Device detected");
					//Получаем capablities устройства.
					GetDeviceCapabilities();
					PrepareForOverlappedTransfer();
				} //if (Attributes.ProductID == ProductID)

				else
					//Product ID не совпадает.
					CloseHandle(DeviceHandle);
			} //if (Attributes.VendorID == VendorID)

			else
				//Vendor ID не совпадает.
				CloseHandle(DeviceHandle);

		//Освобождаем память, используемую структурой detailData (она больше не нужна).
		free(detailData);
		}  //if (Result != 0)

		else
			//SetupDiEnumDeviceInterfaces вернул 0, что означает - нет больше устройств для проверки.
			LastDevice=TRUE;

		//Если мы еще не нашли устройство, и еще не просмотрели все, пробуем следующее.
		MemberIndex = MemberIndex + 1;

	} //do
	while ((LastDevice == FALSE) && (MyDeviceDetected == FALSE));

	if (MyDeviceDetected == FALSE)
		DisplayData("Device not detected");
	else
		DisplayData("Device detected");

	//Освобождаем память, зарезервированную для hDevInfo вызовом SetupDiClassDevs.
	SetupDiDestroyDeviceInfoList(hDevInfo);
	DisplayLastError("SetupDiDestroyDeviceInfoList");

	return MyDeviceDetected;
}

void CUsbhidiocDlg::GetDeviceCapabilities()
{
	//Получение структуры Capabilities для устройства.
	PHIDP_PREPARSED_DATA	PreparsedData;

	/*
	Функция API: HidD_GetPreparsedData
	Возвращает: указатель на буфер, содержащий информацию об capabilities устройства.
	Требует: handle, полученный CreateFile.
	Здесь нам не надо работать с буфером напрямую, но HidP_GetCaps и другие функции API
	требуют указатель на буфер.
	*/

	HidD_GetPreparsedData 
		(DeviceHandle, 
		&PreparsedData);
	DisplayLastError("HidD_GetPreparsedData: ");

	/*
	Функция API: HidP_GetCaps
	Берет возможности (capabilities) устройства.
	Для стандартных устройств типа джойстиков мы можем узнать специфичные capabilities
	устройства. Для custom device программа будет вероятно знать возможности устройства,
	и вызов будет их только проверять.
	Требует: указатель на буфер, полученный HidD_GetPreparsedData.
	Возвращает: структуру Capabilities, содержащую информацию.
	*/
	
	HidP_GetCaps 
		(PreparsedData, 
		&Capabilities);
	DisplayLastError("HidP_GetCaps: ");

	//Отображение capabilities
	ValueToDisplay.Format("%s%X", "Usage Page: ", Capabilities.UsagePage);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Input Report Byte Length: ", Capabilities.InputReportByteLength);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Output Report Byte Length: ", Capabilities.OutputReportByteLength);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Feature Report Byte Length: ", Capabilities.FeatureReportByteLength);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Link Collection Nodes: ", Capabilities.NumberLinkCollectionNodes);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Input Button Caps: ", Capabilities.NumberInputButtonCaps);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of InputValue Caps: ", Capabilities.NumberInputValueCaps);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of InputData Indices: ", Capabilities.NumberInputDataIndices);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Output Button Caps: ", Capabilities.NumberOutputButtonCaps);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Output Value Caps: ", Capabilities.NumberOutputValueCaps);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Output Data Indices: ", Capabilities.NumberOutputDataIndices);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Feature Button Caps: ", Capabilities.NumberFeatureButtonCaps);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Feature Value Caps: ", Capabilities.NumberFeatureValueCaps);
	DisplayData(ValueToDisplay);
	ValueToDisplay.Format("%s%d", "Number of Feature Data Indices: ", Capabilities.NumberFeatureDataIndices);
	DisplayData(ValueToDisplay);

	//PreparsedData больше не нужна, освобождаем память.
	HidD_FreePreparsedData(PreparsedData);
	DisplayLastError("HidD_FreePreparsedData: ") ;
}

void CUsbhidiocDlg::PrepareForOverlappedTransfer()
{
	//Получаем другой handle для устройства, чтобы работал overlapped ReadFiles.
	ReadHandle=CreateFile 
		(detailData->DevicePath, 
		GENERIC_READ|GENERIC_WRITE, 
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		(LPSECURITY_ATTRIBUTES)NULL, 
		OPEN_EXISTING, 
		FILE_FLAG_OVERLAPPED, 
		NULL);
	DisplayLastError("CreateFile (ReadHandle): ");

	//Получаем event object для структуры overlapped.

	/*Функция API: CreateEvent
	  Требует: утрибуты безопасности или Null
	  Ручной сброс (true). Используйте ResetEvent для установки состояния non-signaled 
	  объектов event.
	  Начальное состояние (true = signaled) 
	  Имя Event object (необязательно)
	  Возвращает: хендл на event object
	*/

	if (hEventObject == 0)
	{
		hEventObject = CreateEvent 
			(NULL, 
			TRUE, 
			TRUE, 
			"");
	DisplayLastError("CreateEvent: ") ;

	//Установка полей структуры overlapped.
	HIDOverlapped.hEvent = hEventObject;
	HIDOverlapped.Offset = 0;
	HIDOverlapped.OffsetHigh = 0;
	}
}

void CUsbhidiocDlg::ReadAndWriteToDevice()
{
	//Если мы так уже не сделали, найдите устройство и изучите его возможности.
	//Тогда пошлите репорт и запросите репорт.
	//Тестовое device firmware (usbhidio) добавляет 1 к каждому приянтому байту в 
	// репорте OUT и отправляет обратно результат в следующем репорте IN.

	//Очистка List Box (необязательно).
	//m_ResultsList.ResetContent();

	{
	DisplayData("***HID Test Report***");
	DisplayCurrentTime();

	//Если устройство еще не продетектировано, ищем его.
	if (DeviceDetected==FALSE)
		DeviceDetected=FindTheHID();
	
	if (DeviceDetected==TRUE)
		{
			//Пишем репорт в устройство.
			WriteReport();
			//Читаем репорт из устройства.
			ReadReport();
		} 
	}
}

void CUsbhidiocDlg::ReadReport()
{
	CString	ByteToDisplay = "";
	CString	MessageToDisplay = "";
	DWORD	Result;
	
	//Читаем репорт из устройства.
 	
	/*Вызов API: ReadFile
	Возвращает: репорт в InputReport.
	Требует: device handle, полученный CreateFile
	(для overlapped I/O, CreateFile должен быть вызван с FILE_FLAG_OVERLAPPED),
	длина Input report в байтах, полученная HidP_GetCaps, и структура overlapped structure,
	чье поле hEvent установлено в event object.
	*/

	Result = ReadFile 
		(ReadHandle, 
		InputReport, 
		Capabilities.InputReportByteLength, 
		&NumberOfBytesRead,
		(LPOVERLAPPED) &HIDOverlapped); 
 
	DisplayLastError("ReadFile: ") ;

	/*Вызов API: WaitForSingleObject
	Используется с overlapped ReadFile.
	Делает возврат, когда ReadFile принимает запрошенную порцию данных, или когда 
	заканчивается таймаут.
	Требует event object, созданный CreateEvent и значение таймаута в милисекундах.
	*/

	Result = WaitForSingleObject 
		(hEventObject, 
		6000);
	DisplayLastError("WaitForSingleObject: ") ;
 
	switch (Result)
	{
	case WAIT_OBJECT_0:
		{
		ValueToDisplay.Format("%s", "ReadFile Completed");
		DisplayData(ValueToDisplay);
		break;
		}
	case WAIT_TIMEOUT:
		{
		ValueToDisplay.Format("%s", "ReadFile timeout");
		DisplayData(ValueToDisplay);
		//Отменяем операцию Read.

		/*Вызов API: CancelIo
		Отменяет ReadFile
        Требует device handle.
        Возвращает не ноль, если все ОК.
		*/
		
		Result = CancelIo(ReadHandle);
		
		//Таймаут может означать, чтоустройство было удалено. 
		//Закроем хендлы устройств и установим DeviceDetected = False,
		// чтобы следующая попытка доступа произвела поиск устройства.
		CloseHandle(ReadHandle);
		CloseHandle(DeviceHandle);
		DisplayData("Can't read from device");
		DeviceDetected = FALSE;
		break;
	default:
		ValueToDisplay.Format("%s", "Undefined error");
		break;
		}
	}

	/*
	Вызов API: ResetEvent
	Устанавливает event object в состояние non-signaled.
	Требует handle для event object.
    Возвращает не ноль, если все ОК.
	*/

	ResetEvent(hEventObject);

	//Отображение данных репорта.
	DisplayInputReport();
}

void CUsbhidiocDlg::WriteReport()
{
	//Отправка репорта в устройство.

	//Максимальный размер output report (можно увеличить).
	const unsigned short int	MAXREPORTSIZE = 256;

	DWORD	BytesWritten = 0;
	INT		Index =0;
	CHAR	OutputReport[MAXREPORTSIZE];
	ULONG	Result;
	CString	strBytesWritten = "";

	//Первый байт - номер репорта.
	OutputReport[0]=0;

	//Можно установить другие значения репорта здесь, или получить из из combo-боксов.
	//OutputReport[1]=33;
	//OutputReport[2]=6;
	//OutputReport[3]=15;

	//Получение байтов для отправки из combo-боксов.
	
	//Если галочка Autoincrement установлена, увеличиваем выбор.
	if (m_cbutAutoIncrement.GetCheck()>0)
	{
		Index=m_cboByteToSend0.GetCurSel();
		Index=Index+1;
		m_cboByteToSend0.SetCurSel(Index);
	}

	if (m_cbutAutoIncrement.GetCheck()>0)
	{
		Index=m_cboByteToSend1.GetCurSel();
		Index=Index+1;
		m_cboByteToSend1.SetCurSel(Index);
	}

	//Получаем величины из комбо-боксов.
	OutputReport[1]=m_cboByteToSend0.GetCurSel();
	OutputReport[2]=m_cboByteToSend1.GetCurSel();

	/*
	Функция API: WriteFile
	Отправляет репорт в устройство.
	Возвращает: успех или ошибка.
	Требует:
	device handle, полученное CreateFile.
	Длина Output Report, полученная HidP_GetCaps,
	репорт для отправки.
	*/

	Result = WriteFile 
		(DeviceHandle, 
		OutputReport, 
		Capabilities.OutputReportByteLength, 
		&BytesWritten, 
		NULL);

	if (Result == 0)
	{
		//WriteFile завершился с ошибкой, закрываем handle, отображаем сообщение
		// и устанавливаем DeviceDetected в FALSE, чтобы в следующий раз был произведен поиск
		// устройства.
		CloseHandle(DeviceHandle);
		CloseHandle(ReadHandle);
		DisplayData("Can't write to device");
		DeviceDetected = FALSE;
	}
	
	//Отрображение результата вызова API и байтов репорта.
	DisplayLastError("WriteFile: ");
	strBytesWritten.Format("%s%d", "Bytes Written: ", BytesWritten); 
	DisplayData(strBytesWritten);
}

/*
Подпрограммы отображения
*/

void CUsbhidiocDlg::DisplayInputReport()
{
	USHORT	ByteNumber;
	CHAR	ReceivedByte;
	
	//Отображение принятых данных в лог и лист-боксы Bytes Received.
	//Начало - с вершины List Box.
	m_BytesReceived.ResetContent();
	
	//Перебор всех приянтых байт и отображение каждого.
	for (ByteNumber=0; ByteNumber < Capabilities.InputReportByteLength; ByteNumber++)
	{
		//Get a byte.
		ReceivedByte = InputReport[ByteNumber];
		//Display it.
		DisplayReceivedData(ReceivedByte);
	}
}

void CUsbhidiocDlg::DisplayCurrentTime()
{
	//Получение текущего времени и даты, и отображение их в логе List Box.
	CTime curTime = CTime::GetCurrentTime();
	CString CurrentTime = curTime.Format( "%H:%M:%S, %B %d, %Y" );
	DisplayData(CurrentTime);
}

void CUsbhidiocDlg::DisplayData(CString cstrDataToDisplay)
{
	//Отображение данных в логе List Box
	USHORT	Index;
	Index=m_ResultsList.InsertString(-1, (LPCTSTR)cstrDataToDisplay);
	ScrollToBottomOfListBox(Index);
}

void CUsbhidiocDlg::DisplayLastError(CString Operation)
{
	//Отображение сообщения о последней ошибке в логе List Box. 
	LPVOID lpMsgBuf;
	USHORT Index = 0;
	CString	strLastError = "";
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);

	//Отображение last error.
	strLastError = Operation + (LPCTSTR)lpMsgBuf; 
	//Удалим CR/LF из error message.
	strLastError.TrimRight(); 
	Index = m_ResultsList.InsertString(-1, strLastError);
	ScrollToBottomOfListBox(Index);
	LocalFree(lpMsgBuf); 
}

void CUsbhidiocDlg::DisplayReceivedData(char ReceivedByte)
{
	//Отображение принятых от устройства данных.
	CString	strByteRead;
	//Преобразование значения в двухсимвольный Cstring.
	strByteRead.Format("%02X", ReceivedByte);
	strByteRead = strByteRead.Right(2); 
	//Отображение величины в лист-боксе Bytes Received.
	m_BytesReceived.InsertString(-1, strByteRead);
	//Отображение величины в логе List Box (необязательно).
	//MessageToDisplay.Format("%s%s", "Byte 0: ", strByteRead); 
	//DisplayData(MessageToDisplay);
}

void CUsbhidiocDlg::OnChangeResults() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
}

void CUsbhidiocDlg::ScrollToBottomOfListBox(USHORT Index)
{
	/* 
	Прокрутка лист-бокса в конец. 
	Чтобы сделать это, выбираем строку, что возможно сделает прокрутку, и затем отменяем 
	выбор.
	*/

	m_ResultsList.SetCurSel( Index );
	m_ResultsList.SetCurSel( -1 );
}

/*
Разные подпрограммы.
*/

void CUsbhidiocDlg::OnTimer(UINT nIDEvent) 
{
	//Событие таймера.
	//Read и Write одну пару репортов.
	ReadAndWriteToDevice();

	CDialog::OnTimer(nIDEvent);
}

void CUsbhidiocDlg::OnOK() 
{
	CDialog::OnOK();
}



