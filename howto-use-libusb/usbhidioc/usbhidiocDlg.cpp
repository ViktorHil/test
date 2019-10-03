// usbhidiocDlg.cpp : implementation file
/*
Project: usbhidioc.cpp
Version: 2.0
Date: 12/20/00
by Jan Axelson (jan@lvr.com)

����������: ������������ USB ������������ HID-class device � �������������� overlapped I/O.

��������: 
	��������� �������������� HID-class device, ������� ������������� �������� vendor & product IDs.
	��������� device capabilities.
	���������� 2 ����� � ���������� � �������������� Input reports.
	����������� 2 ����� �� ���������� � �������������� Output reports. 
	List box ���������� ��� ����������.
	List box Bytes Received ���������� ����� ����� �������� ����� �������.
	Combo-����� ��������� ������������ ������� ����� ��� ��������.
	������� "autoincrement" �������� ������������� ���������� ���������� ���� � ������ �������.
	������ �� ������ "Once" ��������� ����� ����� ������� ��������.
	������ �� ������ "Continuous" ��������� ����� ��������� ������������ ������ 5 ������).
	
���������� ���� ������� � Visual C++ 6 � ������� AppWizard �� ������ ������� "dialog-based application".

��������������� firmware � ������ ������� �������� �� www.lvr.com.

��������� �� ������ Usenet � �������� ����� www.deja.com/usenet, ������� ������� ��� 
� Visual C++ � ���� �������. ������ ���������, ������� � ����������� - www.natsemi.com
� �������� HID application � John Hyde's terminal program �� www.usb-by-example.com.

�������� ��������� �� ��������� � ���������� ������� - ������������� overlapped I/O.

��������� �����������, �������, ��������� �� ������� � ����. �� jan@lvr.com.

[�� overlapped I/O]

������ HID input reports �������������� � API �������� ReadFile. 
Non-overlapped ReadFile �������� ����������� �������. ���� ���������� �� ���������� 
��������� ���������� ������, ���������� ��������, ��� ��� �������� ���������� ����������.

� ������������� overlapped I/O ����� ReadFile ���������� � ����������� ���������. ���������� 
��������� WaitForSingleObject, ������� ������������ ���� ����� ������ ������, ���� ����� 
��������� ��������� �������.

��� ��������� ���� �������������� � Windows 98 SE � Windows 2000.
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

	//������ ���� �����������
	int		ByteToSend =0;
	CString	strByteToSend = "";
	CString	strComboBoxText="";
	//����� ���� �����������

	// ���������� � ��������� ���� ������ "About...".

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
	��� ��� ���������� �����. ���, ��� ����� ��������� ��� ������
	����������, ���������� �����.
	*/

	//��������� combo boxes ���������� �� 00 �� FF.
	DeviceDetected=FALSE;

	for (ByteToSend=0; ByteToSend < 256; ByteToSend++)
	{
		//���������� �������� ��� 2-digit Hex value.
		strByteToSend.Format("%.2X",ByteToSend);
		m_cboByteToSend0.AddString(strByteToSend);
		m_cboByteToSend1.AddString(strByteToSend);	
	}

	//����� �������� �� ��������� � combo boxes.
	m_cboByteToSend0.SetCurSel(0);
	m_cboByteToSend1.SetCurSel(128);

	//������ ������� � autoincrement check box.
	m_cbutAutoIncrement.SetCheck(1);

	//������������� ������� �� ������ "Continous".
	m_Continuous.SetWindowText("Continuous");
	//����� ����� ����

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
	//������ �� ������ "Continuous" ��������� ��� �������������
	// ������� � �������� ������������� ��������.
	CString Caption;

	//����������, � ����� ��������� ������ - �� ����� 
	// ������� ���������� ��������.
	m_Continuous.GetWindowText(Caption);
	if (Caption == "Continuous")
	{
		//���������� ������������� ������� ���������.
		//�������� ������� �� ������.
		m_Continuous.SetWindowText("Stop Continuous");
		//�������� ������ � ������ ���� ��������.
		ReadAndWriteToDevice();
		//�������� ������ ��� ������������� �������� ��������.
		//������ �������� - ����� ���������� ����� report requests.
		SetTimer(ID_CLOCK_TIMER, 5000, NULL);
	}
	else
	{
		//��������� �������������� ������ ���������.
		//�������� ������� �� ������.
		m_Continuous.SetWindowText("Continuous");
		//��������� ������.
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
	//������������� ����� ������� API ��� ���������� HID � ����������� Vendor � Product ID.

	HIDD_ATTRIBUTES						Attributes;
	SP_DEVICE_INTERFACE_DATA			devInfoData;
	bool								LastDevice = FALSE;
	int									MemberIndex = 0;
	bool								MyDeviceDetected = FALSE; 
	LONG								Result;

	//��� ������� ��������� Vendor ID � Product ID.
	//������������ Lakeview Research's Vendor ID.
	//const unsigned int VendorID = 0x0925;
	//const unsigned int ProductID = 0x1234;
	//� ��� � ��������� ��� obdev-��������� (������������ � ������� firmware hid-custom-rq):
	const unsigned int VendorID = 0x16c0;
	const unsigned int ProductID = 0x05df;

	Length = 0;
	detailData = NULL;
	DeviceHandle=NULL;

	/*
	������� API: HidD_GetHidGuid
	��������� GUID ��� ���� HID-�� � �������.
	Returns: GUID � ���������� HidGuid.
	*/
	HidD_GetHidGuid(&HidGuid);	
	
	/*
	������� API: SetupDiGetClassDevs
	Returns: handle � device information set ��� ���� ���������������� devices.
	Requires: GUID, ������������ GetHidGuid.
	*/
	hDevInfo=SetupDiGetClassDevs 
		(&HidGuid, 
		NULL, 
		NULL, 
		DIGCF_PRESENT|DIGCF_INTERFACEDEVICE);
		
	devInfoData.cbSize = sizeof(devInfoData);

	//�������� ���� ��������� ���������, ����� ����� �� ��� ������. 
	//�����, ����� ������� ��������� ����������, ���� ����� ��� ���������� 
	// ��������������, �� ������ �� �������.
	MemberIndex = 0;
	LastDevice = FALSE;

	do
	{
		MyDeviceDetected=FALSE;
		
		/*
		������� API: SetupDiEnumDeviceInterfaces
		�� ������ devInfoData �������� ����� � ��������� 
		SP_DEVICE_INTERFACE_DATA ��� ���������������� ����������.
		�������:
		hDevInfo, ���������� SetupDiGetClassDevs, HidGuid ���������� �� GetHidGuid,
		������ ��� �������� ����������.
		*/
		Result=SetupDiEnumDeviceInterfaces 
			(hDevInfo, 
			0, 
			&HidGuid, 
			MemberIndex, 
			&devInfoData);

		if (Result != 0)
		{
			//���������� ����������������, ������� ������ ���������� � ���.
			/*
			������� API: SetupDiGetDeviceInterfaceDetail
			����������: ��������� SP_DEVICE_INTERFACE_DETAIL_DATA,
			���������� ���������� �� ����������.
			��� ��������� ���������� ��� ������� ���������� ������.
			� ������ ��� �������� ������ ��������� � ���������� Length.
			������ ��� �������� ��������� �� ������ � devInfoData.
			�������:
			devInfoData, ���������� ������� SetupDiGetClassDevs,
			��������� SP_DEVICE_INTERFACE_DATA, ���������� ������� SetupDiEnumDeviceInterfaces.
			
			��������� �������� - �������������� ��������� �� ��������� SP_DEV_INFO_DATA.
			��� ���������� �� ���������� ��� ���������.			
			���� ������������� ���������, �� ���������� 
			MyDeviceInfoData.cbSize = length devInfoData, � ��������� ����� ���������.
			*/
			
			//�������� ����� (Length).
			//����� ������ ������ "buffer too small", ������� ����� ���������������.
			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				NULL, 
				0, 
				&Length, 
				NULL);

			//�������� ������ ��� ��������� hDevInfo, ��������� ���������� �����.
			detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(Length);
			
			//Set cbSize in the detailData structure.
			detailData -> cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			//�������� ������� �����, � ���� ��� � ���������� ������ ������.
			Result = SetupDiGetDeviceInterfaceDetail 
				(hDevInfo, 
				&devInfoData, 
				detailData, 
				Length, 
				&Required, 
				NULL);

			//��������� handle � ����������.

			/*
			������� API: CreateFile
			�������: handle, ������� ��������� ������ � ���������� ����������.
			�������:
			DevicePath � ��������� detailData, ������ ��� ������� �������
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
			������� API: HidD_GetAttributes
			����������� ���������� �� ����������.
			�������: handle, ���������� �� CreateFile.
			����������: ��������� HIDD_ATTRIBUTES, ���������� 
			Vendor ID, Product ID, Product Version Number.
			��� ���� ������������ ��� ����������� - �� �� ��� ����������,
			��� �� ����.
			*/

			//��������� Size � ���������� ���� � ���������.
			Attributes.Size = sizeof(Attributes);

			Result = HidD_GetAttributes 
				(DeviceHandle, 
				&Attributes);
			
			DisplayLastError("HidD_GetAttributes: ");
			
			//���������� - ��, ������� �����?
			MyDeviceDetected = FALSE;
			if (Attributes.VendorID == VendorID)
			{
				if (Attributes.ProductID == ProductID)
				{
					//��������� � Product � Vendor ID.
					MyDeviceDetected = TRUE;
					DisplayData("Device detected");
					//�������� capablities ����������.
					GetDeviceCapabilities();
					PrepareForOverlappedTransfer();
				} //if (Attributes.ProductID == ProductID)

				else
					//Product ID �� ���������.
					CloseHandle(DeviceHandle);
			} //if (Attributes.VendorID == VendorID)

			else
				//Vendor ID �� ���������.
				CloseHandle(DeviceHandle);

		//����������� ������, ������������ ���������� detailData (��� ������ �� �����).
		free(detailData);
		}  //if (Result != 0)

		else
			//SetupDiEnumDeviceInterfaces ������ 0, ��� �������� - ��� ������ ��������� ��� ��������.
			LastDevice=TRUE;

		//���� �� ��� �� ����� ����������, � ��� �� ����������� ���, ������� ���������.
		MemberIndex = MemberIndex + 1;

	} //do
	while ((LastDevice == FALSE) && (MyDeviceDetected == FALSE));

	if (MyDeviceDetected == FALSE)
		DisplayData("Device not detected");
	else
		DisplayData("Device detected");

	//����������� ������, ����������������� ��� hDevInfo ������� SetupDiClassDevs.
	SetupDiDestroyDeviceInfoList(hDevInfo);
	DisplayLastError("SetupDiDestroyDeviceInfoList");

	return MyDeviceDetected;
}

void CUsbhidiocDlg::GetDeviceCapabilities()
{
	//��������� ��������� Capabilities ��� ����������.
	PHIDP_PREPARSED_DATA	PreparsedData;

	/*
	������� API: HidD_GetPreparsedData
	����������: ��������� �� �����, ���������� ���������� �� capabilities ����������.
	�������: handle, ���������� CreateFile.
	����� ��� �� ���� �������� � ������� ��������, �� HidP_GetCaps � ������ ������� API
	������� ��������� �� �����.
	*/

	HidD_GetPreparsedData 
		(DeviceHandle, 
		&PreparsedData);
	DisplayLastError("HidD_GetPreparsedData: ");

	/*
	������� API: HidP_GetCaps
	����� ����������� (capabilities) ����������.
	��� ����������� ��������� ���� ���������� �� ����� ������ ����������� capabilities
	����������. ��� custom device ��������� ����� �������� ����� ����������� ����������,
	� ����� ����� �� ������ ���������.
	�������: ��������� �� �����, ���������� HidD_GetPreparsedData.
	����������: ��������� Capabilities, ���������� ����������.
	*/
	
	HidP_GetCaps 
		(PreparsedData, 
		&Capabilities);
	DisplayLastError("HidP_GetCaps: ");

	//����������� capabilities
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

	//PreparsedData ������ �� �����, ����������� ������.
	HidD_FreePreparsedData(PreparsedData);
	DisplayLastError("HidD_FreePreparsedData: ") ;
}

void CUsbhidiocDlg::PrepareForOverlappedTransfer()
{
	//�������� ������ handle ��� ����������, ����� ������� overlapped ReadFiles.
	ReadHandle=CreateFile 
		(detailData->DevicePath, 
		GENERIC_READ|GENERIC_WRITE, 
		FILE_SHARE_READ|FILE_SHARE_WRITE,
		(LPSECURITY_ATTRIBUTES)NULL, 
		OPEN_EXISTING, 
		FILE_FLAG_OVERLAPPED, 
		NULL);
	DisplayLastError("CreateFile (ReadHandle): ");

	//�������� event object ��� ��������� overlapped.

	/*������� API: CreateEvent
	  �������: �������� ������������ ��� Null
	  ������ ����� (true). ����������� ResetEvent ��� ��������� ��������� non-signaled 
	  �������� event.
	  ��������� ��������� (true = signaled) 
	  ��� Event object (�������������)
	  ����������: ����� �� event object
	*/

	if (hEventObject == 0)
	{
		hEventObject = CreateEvent 
			(NULL, 
			TRUE, 
			TRUE, 
			"");
	DisplayLastError("CreateEvent: ") ;

	//��������� ����� ��������� overlapped.
	HIDOverlapped.hEvent = hEventObject;
	HIDOverlapped.Offset = 0;
	HIDOverlapped.OffsetHigh = 0;
	}
}

void CUsbhidiocDlg::ReadAndWriteToDevice()
{
	//���� �� ��� ��� �� �������, ������� ���������� � ������� ��� �����������.
	//����� ������� ������ � ��������� ������.
	//�������� device firmware (usbhidio) ��������� 1 � ������� ��������� ����� � 
	// ������� OUT � ���������� ������� ��������� � ��������� ������� IN.

	//������� List Box (�������������).
	//m_ResultsList.ResetContent();

	{
	DisplayData("***HID Test Report***");
	DisplayCurrentTime();

	//���� ���������� ��� �� ����������������, ���� ���.
	if (DeviceDetected==FALSE)
		DeviceDetected=FindTheHID();
	
	if (DeviceDetected==TRUE)
		{
			//����� ������ � ����������.
			WriteReport();
			//������ ������ �� ����������.
			ReadReport();
		} 
	}
}

void CUsbhidiocDlg::ReadReport()
{
	CString	ByteToDisplay = "";
	CString	MessageToDisplay = "";
	DWORD	Result;
	
	//������ ������ �� ����������.
 	
	/*����� API: ReadFile
	����������: ������ � InputReport.
	�������: device handle, ���������� CreateFile
	(��� overlapped I/O, CreateFile ������ ���� ������ � FILE_FLAG_OVERLAPPED),
	����� Input report � ������, ���������� HidP_GetCaps, � ��������� overlapped structure,
	��� ���� hEvent ����������� � event object.
	*/

	Result = ReadFile 
		(ReadHandle, 
		InputReport, 
		Capabilities.InputReportByteLength, 
		&NumberOfBytesRead,
		(LPOVERLAPPED) &HIDOverlapped); 
 
	DisplayLastError("ReadFile: ") ;

	/*����� API: WaitForSingleObject
	������������ � overlapped ReadFile.
	������ �������, ����� ReadFile ��������� ����������� ������ ������, ��� ����� 
	������������� �������.
	������� event object, ��������� CreateEvent � �������� �������� � ������������.
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
		//�������� �������� Read.

		/*����� API: CancelIo
		�������� ReadFile
        ������� device handle.
        ���������� �� ����, ���� ��� ��.
		*/
		
		Result = CancelIo(ReadHandle);
		
		//������� ����� ��������, ������������� ���� �������. 
		//������� ������ ��������� � ��������� DeviceDetected = False,
		// ����� ��������� ������� ������� ��������� ����� ����������.
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
	����� API: ResetEvent
	������������� event object � ��������� non-signaled.
	������� handle ��� event object.
    ���������� �� ����, ���� ��� ��.
	*/

	ResetEvent(hEventObject);

	//����������� ������ �������.
	DisplayInputReport();
}

void CUsbhidiocDlg::WriteReport()
{
	//�������� ������� � ����������.

	//������������ ������ output report (����� ���������).
	const unsigned short int	MAXREPORTSIZE = 256;

	DWORD	BytesWritten = 0;
	INT		Index =0;
	CHAR	OutputReport[MAXREPORTSIZE];
	ULONG	Result;
	CString	strBytesWritten = "";

	//������ ���� - ����� �������.
	OutputReport[0]=0;

	//����� ���������� ������ �������� ������� �����, ��� �������� �� �� combo-������.
	//OutputReport[1]=33;
	//OutputReport[2]=6;
	//OutputReport[3]=15;

	//��������� ������ ��� �������� �� combo-������.
	
	//���� ������� Autoincrement �����������, ����������� �����.
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

	//�������� �������� �� �����-������.
	OutputReport[1]=m_cboByteToSend0.GetCurSel();
	OutputReport[2]=m_cboByteToSend1.GetCurSel();

	/*
	������� API: WriteFile
	���������� ������ � ����������.
	����������: ����� ��� ������.
	�������:
	device handle, ���������� CreateFile.
	����� Output Report, ���������� HidP_GetCaps,
	������ ��� ��������.
	*/

	Result = WriteFile 
		(DeviceHandle, 
		OutputReport, 
		Capabilities.OutputReportByteLength, 
		&BytesWritten, 
		NULL);

	if (Result == 0)
	{
		//WriteFile ���������� � �������, ��������� handle, ���������� ���������
		// � ������������� DeviceDetected � FALSE, ����� � ��������� ��� ��� ���������� �����
		// ����������.
		CloseHandle(DeviceHandle);
		CloseHandle(ReadHandle);
		DisplayData("Can't write to device");
		DeviceDetected = FALSE;
	}
	
	//������������ ���������� ������ API � ������ �������.
	DisplayLastError("WriteFile: ");
	strBytesWritten.Format("%s%d", "Bytes Written: ", BytesWritten); 
	DisplayData(strBytesWritten);
}

/*
������������ �����������
*/

void CUsbhidiocDlg::DisplayInputReport()
{
	USHORT	ByteNumber;
	CHAR	ReceivedByte;
	
	//����������� �������� ������ � ��� � ����-����� Bytes Received.
	//������ - � ������� List Box.
	m_BytesReceived.ResetContent();
	
	//������� ���� �������� ���� � ����������� �������.
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
	//��������� �������� ������� � ����, � ����������� �� � ���� List Box.
	CTime curTime = CTime::GetCurrentTime();
	CString CurrentTime = curTime.Format( "%H:%M:%S, %B %d, %Y" );
	DisplayData(CurrentTime);
}

void CUsbhidiocDlg::DisplayData(CString cstrDataToDisplay)
{
	//����������� ������ � ���� List Box
	USHORT	Index;
	Index=m_ResultsList.InsertString(-1, (LPCTSTR)cstrDataToDisplay);
	ScrollToBottomOfListBox(Index);
}

void CUsbhidiocDlg::DisplayLastError(CString Operation)
{
	//����������� ��������� � ��������� ������ � ���� List Box. 
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

	//����������� last error.
	strLastError = Operation + (LPCTSTR)lpMsgBuf; 
	//������ CR/LF �� error message.
	strLastError.TrimRight(); 
	Index = m_ResultsList.InsertString(-1, strLastError);
	ScrollToBottomOfListBox(Index);
	LocalFree(lpMsgBuf); 
}

void CUsbhidiocDlg::DisplayReceivedData(char ReceivedByte)
{
	//����������� �������� �� ���������� ������.
	CString	strByteRead;
	//�������������� �������� � �������������� Cstring.
	strByteRead.Format("%02X", ReceivedByte);
	strByteRead = strByteRead.Right(2); 
	//����������� �������� � ����-����� Bytes Received.
	m_BytesReceived.InsertString(-1, strByteRead);
	//����������� �������� � ���� List Box (�������������).
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
	��������� ����-����� � �����. 
	����� ������� ���, �������� ������, ��� �������� ������� ���������, � ����� �������� 
	�����.
	*/

	m_ResultsList.SetCurSel( Index );
	m_ResultsList.SetCurSel( -1 );
}

/*
������ ������������.
*/

void CUsbhidiocDlg::OnTimer(UINT nIDEvent) 
{
	//������� �������.
	//Read � Write ���� ���� ��������.
	ReadAndWriteToDevice();

	CDialog::OnTimer(nIDEvent);
}

void CUsbhidiocDlg::OnOK() 
{
	CDialog::OnOK();
}



