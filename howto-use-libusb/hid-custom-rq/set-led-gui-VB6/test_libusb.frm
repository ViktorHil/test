VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   990
   ClientLeft      =   8520
   ClientTop       =   6840
   ClientWidth     =   2175
   LinkTopic       =   "Form1"
   ScaleHeight     =   990
   ScaleWidth      =   2175
   Begin VB.CheckBox Check1 
      Caption         =   "Светодиод горит"
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1815
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim cnt As Long
Dim isOn As Long

Private Sub Check1_Click()
WRITE_USB (Check1)
End Sub

Private Sub Form_Activate()
    UsbInit
    UsbSetDebug (255)
    Check1 = READ_USB
End Sub

Private Function READ_USB() As Byte
Dim dev As Long
Dim buffer As Byte
    dev = UsbOpen(0, &H16C0, &H5DF)
    If dev > 0 Then
        'прием
        cnt = UsbControlMsg(dev, &HC0, 2, 0, 0, buffer, 1, 5000)
        READ_USB = buffer
        UsbClose (dev)
    Else
        READ_USB = 0
        MsgBox ("Немогу найти устройство VID = 160C ,PID = 5DF")
    End If
End Function

Private Function WRITE_USB(isOn As Long) As Byte
Dim buffer As Byte
Dim dev As Long
    dev = UsbOpen(0, &H16C0, &H5DF)
    If dev > 0 Then
            'передача
        cnt = UsbControlMsg(dev, &H40, 1, isOn, 0, buffer, 0, 5000)
        WRITE_USB = 1
        UsbClose (dev)
    Else
          WRITE_USB = 0
          MsgBox ("Немогу найти устройство VID = 160C ,PID = 5DF")
    End If
End Function




