Structure RGB
  Dim R As Byte
  Dim G As Byte
  Dim B As Byte
End Structure 

Structure ExecParms
  Dim TextString As String  ' text to be scrolled around the LED cube
  Dim Delay      As Byte    ' number of frames to delay before incrementing text movement 
  Dim Decay      As Boolean ' use progressive illumination/decay to smooth movement during delay
  Dim Cycles     As Integer ' number of complete rotations of text around the cube 
  Dim Background As String  ' supported values: "void" | "asis" | "fill" | "edge"    
  Dim BackColor  As RGB     ' only required for ExecParms.Background="fill" | "edge"
  Dim Foreground As String  ' supported values: "rainbow" | "color"
  Dim ForeColor  As RGB     ' only required when ExecParms.Foreground="color"
End Structure

Public Sub Main() Implements scriptInterface.IScript.Main
Try
'-------------------------------------------------------------------------------
' MARQUEE.VB - Cubesense VB Script for eightCubed V2 LED cube 
'
' Scroll a string of raster-pattern text characters around the perimeter of an 
' eightCubed V2 RGB LED cube, in the manner of a marquee light display. Works 
' with any cubic or rectangular lattice having a minimum height (z-dimension) 
' of 8 voxels
'
' Author:   Kurt A. Koehler
' Date:     June 2011
'
' CHANGE HISTORY 
' 
' 07/11/11: version 2.0 - added a 'progressive illumination/decay' technique to 
'           cause the colors of leading and trailing text LEDs to 'fade in' and
'           'fade out' during a delay cycle, helping to create a an illusion  
'           of smoother image movement
'-------------------------------------------------------------------------------
'
' EXECUTION OPTIONS - (values can be set in code immediately below this comment 
'                      block)
'
' - Options.TextString is the text value of the marquee message and can contain 
'   any combination of upper-case, lower-case, numeric and special text characters.
'
' - Options.Delay is a numeric integer specifying how many times a text pattern
'   is to be repeated in successive frames before the next (incremental) movement
'   of the marquee text is generated; the lower the value, the faster the text moves.
'   Value must be a positive integer or 0, default value of Options.Delay is 6.   
'
' - Options.Decay is a boolean value indicating whether a a progressive illumination
'   and decay technique is to be used create the illusion of smooth movement during
'   the Options.Delay period. Default value of Options.Decay is True.  
'
' - Options.Background is a text value that specifies the preferred method of 
'   illuminating lights in the cube 'behind' the text and can have values of:
'   "void"    - clears the color values (to RGB 0,0,0) of all LEDs in each frame 
'               before generating the marquee text
'   "asis"    - leaves any exisiting frame content intact but overlays text on 
'               the cube perimeter (useful for adding a marquee to another 
'               animation)
'   "fill"    - fills entire cube with a solid color before rendering the text 
'               pattern; Options.BackColor R, G and B values must also be supplied
'   "edge"    - fills only the LEDs on the outer perimeter of the cube with a 
'               solid color before rendering the text pattern; Options.BackColor 
'               R, G and B values must also be supplied
'   Default value of Options.Background is "void". 
'
' - Options.Foreground is a text value that specifies the preferred method of 
'   illuminating lights in the text raster pattern and can have values of:
'   "rainbow" - raster text is presented using a 'rainbow' gradient of color, 
'               incrementally changing as it scrolls across the face of the cube
'   "color"   - text is presented using a solid color value;  Options.BackColor 
'               R, G and B values must also be supplied
'   Default value of Options.Foreground is "rainbow"
'
' - Options.Foreground and Options.Background. R, G and B variables are integer values 
'   in the range of 0 - 255 that specify the I of Red, Green and Blue
'   components of the text foreground or cube background colors. 

  Dim Options             As ExecParms
  Options.TextString  = "www.Lumisense.com - Home to eightCubed & Cubesense"
  Options.Delay       = 6
  Options.Decay       = True 
  Options.Cycles      = 1 
  Options.Background  = "void"
  Options.BackColor.R = 0
  Options.BackColor.G = 0
  Options.BackColor.B = 0
  Options.Foreground  = "rainbow"
  Options.ForeColor.R = 255
  Options.ForeColor.G = 255
  Options.ForeColor.B = 255 

' Variables - Declaration & Initialization

  Dim InputString         As String
  Dim Line (7)            As String 
  Dim msgText             As String
  Dim r, rr, g, gg, b, bb As Integer 
  Dim CrLf                As String = Environment.NewLine
  Dim i, j, k, l, c       As Integer
  Dim xx, yy, zz, dK      As Integer 
  Dim pctDecay            As Decimal = 0.000
  Dim I1                  As Decimal = 0.000
  Dim I2                  As Decimal = 0.000
  Dim frameCount          As Integer = cs.getFrameCount() - 1
  Dim totalFrames         As Integer = 0
  Dim response            As Integer = 0
  Dim f                   As Integer = 0
  Dim xSize               As Integer = cs.getSizeX()
  Dim ySize               As Integer = cs.getSizeY()
  Dim zSize               As Integer = cs.getSizeZ()
  Dim xMax                As Integer = xSize - 1
  Dim yMax                As Integer = ySize - 1
  Dim zMax                As Integer = zSize - 1
  Dim xMin                As Integer = 0
  Dim yMin                As Integer = 0
  Dim zMin                As Integer = 0
  Dim x                   As Integer = 0
  Dim y                   As Integer = 0
  Dim z                   As Integer = 0

' Terminate processing if the LED cube is too short to display the Marquee text characters

  If zSize < 8 Then
    System.Windows.Forms.MessageBox.Show ("Error: The Z-dimension of the cube is too small for a Marquee" & _
      " animation - your cube must be at least 8 LEDs in height for the text characters to display" & _
      CrLf & CrLf & "Processing is terminated.", _
      "Marquee.VB Script", _
      System.Windows.Forms.MessageBoxButtons.OK, _
      System.Windows.Forms.MessageBoxIcon.Stop)
    Exit Sub
  End If

' Block text characters raster pattern definitions
' First ASCII char0: 32, last ASCII char = 127 (total=96) 

  Dim BlockText(,) As String = New String(0 To 95, 0 To 7) { _
{"   ", _
 "   ", _
 "   ", _
 "   ", _
 "   ", _
 "   ", _
 "   ", _
 "   "}, _
{"  # ", _
 " ###", _
 " ###", _
 "  # ", _
 "  # ", _
 "    ", _
 "  # ", _
 "    "}, _
{" # #", _
 " # #", _
 "    ", _
 "    ", _
 "    ", _
 "    ", _
 "    ", _
 "    "}, _
{"      ", _
 "  # # ", _
 " #####", _
 "  # # ", _
 "  # # ", _
 " #####", _
 "  # # ", _
 "      "}, _
{"   #  ", _
 "  ####", _
 " # #  ", _
 "  ### ", _
 "   # #", _
 " #### ", _
 "   #  ", _
 "      "}, _
{" ##   ", _
 " ##  #", _
 "    # ", _
 "   #  ", _
 "  #   ", _
 " #  ##", _
 "    ##", _
 "      "}, _
{"  #   ", _
 " # #  ", _
 " # #  ", _
 "  #   ", _
 " # # #", _
 " #  # ", _
 "  ## #", _
 "      "}, _
{" #", _
 " #", _
 "  ", _
 "  ", _
 "  ", _
 "  ", _
 "  ", _
 "  "}, _
{"   #", _
 "  # ", _
 "  # ", _
 "  # ", _
 "  # ", _
 "  # ", _
 "   #", _
 "    "}, _
{"  # ", _
 "   #", _
 "   #", _
 "   #", _
 "   #", _
 "   #", _
 "  # ", _
 "    "}, _
{"      ", _
 "  # # ", _
 "  ### ", _
 " #####", _
 "  ### ", _
 "  # # ", _
 "      ", _
 "      "}, _
{"      ", _
 "   #  ", _
 "   #  ", _
 " #####", _
 "   #  ", _
 "   #  ", _
 "      ", _
 "      "}, _
{"   ", _
 "   ", _
 "   ", _
 "   ", _
 "   ", _
 "   ", _
 "  #", _
 " # "}, _
{"      ", _
 "      ", _
 "      ", _
 " #####", _
 "      ", _
 "      ", _
 "      ", _
 "      "}, _
{"  ", _
 "  ", _
 "  ", _
 "  ", _
 "  ", _
 "  ", _
 " #", _
 "  "}, _
{"      ", _
 "     #", _
 "    # ", _
 "   #  ", _
 "  #   ", _
 " #    ", _
 "      ", _
 "      "}, _
{"  ### ", _
 " #   #", _
 " #  ##", _
 " # # #", _
 " ##  #", _
 " #   #", _
 "  ### ", _
 "      "}, _
{"   # ", _
 "  ## ", _
 "   # ", _
 "   # ", _
 "   # ", _
 "   # ", _
 "  ###", _
 "     "}, _
{"  ### ", _
 " #   #", _
 "     #", _
 "    # ", _
 "   #  ", _
 "  #   ", _
 " #####", _
 "      "}, _
{"  ### ", _
 " #   #", _
 "     #", _
 "  ### ", _
 "     #", _
 " #   #", _
 "  ### ", _
 "      "}, _
{"    # ", _
 "   ## ", _
 "  # # ", _
 " #  # ", _
 " #####", _
 "    # ", _
 "    # ", _
 "      "}, _
{" #####", _
 " #    ", _
 " #    ", _
 " #### ", _
 "     #", _
 " #   #", _
 "  ### ", _
 "      "}, _
{"   ## ", _
 "  #   ", _
 " #    ", _
 " #### ", _
 " #   #", _
 " #   #", _
 "  ### ", _
 "      "}, _
{" #####", _
 "     #", _
 "    # ", _
 "   #  ", _
 "  #   ", _
 "  #   ", _
 "  #   ", _
 "      "}, _
{"  ### ", _
 " #   #", _
 " #   #", _
 "  ### ", _
 " #   #", _
 " #   #", _
 "  ### ", _
 "      "}, _
{"  ### ", _
 " #   #", _
 " #   #", _
 "  ####", _
 "     #", _
 "    # ", _
 "  ##  ", _
 "      "}, _
{"  ", _
 "  ", _
 "  ", _
 " #", _
 "  ", _
 "  ", _
 " #", _
 "  "}, _
{"   ", _
 "   ", _
 "   ", _
 "  #", _
 "   ", _
 "   ", _
 "  #", _
 " # "}, _
{"    #", _
 "   # ", _
 "  #  ", _
 " #   ", _
 "  #  ", _
 "   # ", _
 "    #", _
 "     "}, _
{"      ", _
 "      ", _
 " #####", _
 "      ", _
 " #####", _
 "      ", _
 "      ", _
 "      "}, _
{" #   ", _
 "  #  ", _
 "   # ", _
 "    #", _
 "   # ", _
 "  #  ", _
 " #   ", _
 "     "}, _
{"  ### ", _
 " #   #", _
 "     #", _
 "   ## ", _
 "   #  ", _
 "      ", _
 "   #  ", _
 "      "}, _
{"  ### ", _
 " #   #", _
 " # ###", _
 " # # #", _
 " # ###", _
 " #    ", _
 "  ### ", _
 "      "}, _
{"  ### ", _
 " #   #", _
 " #   #", _
 " #####", _
 " #   #", _
 " #   #", _
 " #   #", _
 "      "}, _
{" #### ", _
 " #   #", _
 " #   #", _
 " #### ", _
 " #   #", _
 " #   #", _
 " #### ", _
 "      "}, _
{"  ### ", _
 " #   #", _
 " #    ", _
 " #    ", _
 " #    ", _
 " #   #", _
 "  ### ", _
 "      "}, _
{" #### ", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #### ", _
 "      "}, _
{" #####", _
 " #    ", _
 " #    ", _
 " #### ", _
 " #    ", _
 " #    ", _
 " #####", _
 "      "}, _
{" #####", _
 " #    ", _
 " #    ", _
 " #### ", _
 " #    ", _
 " #    ", _
 " #    ", _
 "      "}, _
{"  ### ", _
 " #   #", _
 " #    ", _
 " # ###", _
 " #   #", _
 " #   #", _
 "  ### ", _
 "      "}, _
{" #   #", _
 " #   #", _
 " #   #", _
 " #####", _
 " #   #", _
 " #   #", _
 " #   #", _
 "      "}, _
{"  ### ", _
 "   #  ", _
 "   #  ", _
 "   #  ", _
 "   #  ", _
 "   #  ", _
 "  ### ", _
 "      "}, _
{"     #", _
 "     #", _
 "     #", _
 "     #", _
 " #   #", _
 " #   #", _
 "  ### ", _
 "      "}, _
{" #   #", _
 " #  # ", _
 " # #  ", _
 " ##   ", _
 " # #  ", _
 " #  # ", _
 " #   #", _
 "      "}, _
{" #    ", _
 " #    ", _
 " #    ", _
 " #    ", _
 " #    ", _
 " #    ", _
 " #####", _
 "      "}, _
{" #   #", _
 " ## ##", _
 " # # #", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #   #", _
 "      "}, _
{" #   #", _
 " ##  #", _
 " # # #", _
 " #  ##", _
 " #   #", _
 " #   #", _
 " #   #", _
 "      "}, _
{"  ### ", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #   #", _
 "  ### ", _
 "      "}, _
{" #### ", _
 " #   #", _
 " #   #", _
 " #### ", _
 " #    ", _
 " #    ", _
 " #    ", _
 "      "}, _
{"  ### ", _
 " #   #", _
 " #   #", _
 " #   #", _
 " # # #", _
 " #  # ", _
 "  ## #", _
 "      "}, _
{" #### ", _
 " #   #", _
 " #   #", _
 " #### ", _
 " #  # ", _
 " #   #", _
 " #   #", _
 "      "}, _
{"  ### ", _
 " #   #", _
 " #    ", _
 "  ### ", _
 "     #", _
 " #   #", _
 "  ### ", _
 "      "}, _
{" #####", _
 "   #  ", _
 "   #  ", _
 "   #  ", _
 "   #  ", _
 "   #  ", _
 "   #  ", _
 "      "}, _
{" #   #", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #   #", _
 "  ### ", _
 "      "}, _
{" #   #", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #   #", _
 "  # # ", _
 "   #  ", _
 "      "}, _
{" #   #", _
 " #   #", _
 " # # #", _
 " # # #", _
 " # # #", _
 " # # #", _
 "  # # ", _
 "      "}, _
{" #   #", _
 " #   #", _
 "  # # ", _
 "   #  ", _
 "  # # ", _
 " #   #", _
 " #   #", _
 "      "}, _
{" #   #", _
 " #   #", _
 " #   #", _
 "  # # ", _
 "   #  ", _
 "   #  ", _
 "   #  ", _
 "      "}, _
{" #### ", _
 "    # ", _
 "   #  ", _
 "  #   ", _
 " #    ", _
 " #    ", _
 " #### ", _
 "      "}, _
{"  ###", _
 "  #  ", _
 "  #  ", _
 "  #  ", _
 "  #  ", _
 "  #  ", _
 "  ###", _
 "     "}, _
{"      ", _
 " #    ", _
 "  #   ", _
 "   #  ", _
 "    # ", _
 "     #", _
 "      ", _
 "      "}, _
{"  ###", _
 "    #", _
 "    #", _
 "    #", _
 "    #", _
 "    #", _
 "  ###", _
 "     "}, _
{"   #  ", _
 "  # # ", _
 " #   #", _
 "      ", _
 "      ", _
 "      ", _
 "      ", _
 "      "}, _
{"      ", _
 "      ", _
 "      ", _
 "      ", _
 "      ", _
 "      ", _
 "      ", _
 "######"}, _
{" ## ", _
 " ## ", _
 "   #", _
 "    ", _
 "    ", _
 "    ", _
 "    ", _
 "    "}, _
{"      ", _
 "      ", _
 "  ### ", _
 "     #", _
 "  ####", _
 " #   #", _
 "  ####", _
 "      "}, _
{" #    ", _
 " #    ", _
 " #### ", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #### ", _
 "      "}, _
{"      ", _
 "      ", _
 "  ### ", _
 " #   #", _
 " #    ", _
 " #   #", _
 "  ### ", _
 "      "}, _
{"     #", _
 "     #", _
 "  ####", _
 " #   #", _
 " #   #", _
 " #   #", _
 "  ####", _
 "      "}, _
{"      ", _
 "      ", _
 "  ### ", _
 " #   #", _
 " #####", _
 " #    ", _
 "  ### ", _
 "      "}, _
{"   ##", _
 "  #  ", _
 " ####", _
 "  #  ", _
 "  #  ", _
 "  #  ", _
 "  #  ", _
 "     "}, _
{"      ", _
 "      ", _
 "  ### ", _
 " #   #", _
 " #   #", _
 "  ####", _
 "     #", _
 "  ### "}, _
{" #    ", _
 " #    ", _
 " #### ", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #   #", _
 "      "}, _
{" #", _
 "  ", _
 " #", _
 " #", _
 " #", _
 " #", _
 " #", _
 "  "}, _
{"    #", _
 "     ", _
 "    #", _
 "    #", _
 "    #", _
 "    #", _
 " #  #", _
 "  ## "}, _
{" #   ", _
 " #   ", _
 " #  #", _
 " # # ", _
 " ##  ", _
 " # # ", _
 " #  #", _
 "     "}, _
{" #", _
 " #", _
 " #", _
 " #", _
 " #", _
 " #", _
 " #", _
 "  "}, _
{"      ", _
 "      ", _
 " ## # ", _
 " # # #", _
 " # # #", _
 " #   #", _
 " #   #", _
 "      "}, _
{"      ", _
 "      ", _
 " #### ", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #   #", _
 "      "}, _
{"      ", _
 "      ", _
 "  ### ", _
 " #   #", _
 " #   #", _
 " #   #", _
 "  ### ", _
 "      "}, _
{"      ", _
 "      ", _
 " #### ", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #### ", _
 " #    "}, _
{"      ", _
 "      ", _
 "  ####", _
 " #   #", _
 " #   #", _
 " #   #", _
 "  ####", _
 "     #"}, _
{"      ", _
 "      ", _
 " # ## ", _
 " ##  #", _
 " #    ", _
 " #    ", _
 " #    ", _
 "      "}, _
{"      ", _
 "      ", _
 "  ### ", _
 " #    ", _
 "  ### ", _
 "     #", _
 "  ### ", _
 "      "}, _
{"     ", _
 "  #  ", _
 " ####", _
 "  #  ", _
 "  #  ", _
 "  #  ", _
 "   ##", _
 "     "}, _
{"      ", _
 "      ", _
 " #   #", _
 " #   #", _
 " #   #", _
 " #   #", _
 "  ### ", _
 "      "}, _
{"      ", _
 "      ", _
 " #   #", _
 " #   #", _
 " #   #", _
 "  # # ", _
 "   #  ", _
 "      "}, _
{"      ", _
 "      ", _
 " #   #", _
 " #   #", _
 " # # #", _
 " #####", _
 "  # # ", _
 "      "}, _
{"      ", _
 "      ", _
 " #   #", _
 "  # # ", _
 "   #  ", _
 "  # # ", _
 " #   #", _
 "      "}, _
{"      ", _
 "      ", _
 " #   #", _
 " #   #", _
 " #   #", _
 "  ####", _
 "     #", _
 "  ### "}, _
{"      ", _
 "      ", _
 " #####", _
 "    # ", _
 "   #  ", _
 "  #   ", _
 " #####", _
 "      "}, _
{"   ##", _
 "  #  ", _
 "  #  ", _
 " ##  ", _
 "  #  ", _
 "  #  ", _
 "   ##", _
 "     "}, _
{" #", _
 " #", _
 " #", _
 "  ", _
 " #", _
 " #", _
 " #", _
 "  "}, _
{" ##  ", _
 "   # ", _
 "   # ", _
 "   ##", _
 "   # ", _
 "   # ", _
 " ##  ", _
 "     "}, _
{"  # #", _
 " # # ", _
 "     ", _
 "     ", _
 "     ", _
 "     ", _
 "     ", _
 "     "}, _
{"   #  ", _
 "  ### ", _
 " ## ##", _
 " #   #", _
 " #   #", _
 " #####", _
 "      ", _
 "      "} _
 }

' Prompt for the text to be presented on the LED cube marquee 

 InputString = Microsoft.VisualBasic.Interaction.InputBox _
   ("Enter the text string you want to see scrolled across the face of the LED cube:", _
   "Marquee.VB Script", _
   Options.TextString)
 
 If InputString = "" Then Exit Sub
 
 Options.TextString = InputString
 
' Initialize TextString to all ASCII text characters (for testing font design changes only) 

' Options.TextString = ""
' For i = 32 to 127
'    Options.TextString = Options.TextString & Convert.ToChar(i)
' Next

' Construct the 'Line' array to contain the raster patterns of all characters 
' in 'Options.TextString' 

  L = Options.TextString.Length - 1

  For j = 0 to L ' for each character in Options.TextString... 
    k = Convert.ToInt32 (Convert.ToChar (Options.TextString.Substring (j, 1))) - 32

'   Append the raster pattern of each character in 'Options.TextString' to the 'Line' array

    For i = 0 to 7
      Line (i) = Line (i) + BlockText (k, i)
    Next
  Next

' Add a number of blank characters to the beginning and end of the Raster Pattern 
' equal to the total number of columns of LEDs around the perimeter of the cube. 

  For i = 0 to 7
    Line (i) = String.empty.PadLeft (2 * (xMax + yMax), " "c) + Line (i) + _
               String.empty.PadLeft (2 * (xMax + yMax), " "c) 
  Next 

' Set the value of L to the total number of columns contained in the raster pattern  
' of text to be rotated about the perimeter of the cube, including the leading blanks 

  L = Line(0).Length - 2 * (xMax + yMax) 

' Calculate the total number of frames that will be required by this animation and compare
' it to the value returned by cs.getFrameCount(), the number of frames defined in the 
' 'Frames List'; if they are unequal, display an appropriate warning mesage to the user 
' before proceeding to compute the frame content for the marquee display.

  totalFrames =  L * Options.Cycles * (Options.Delay + 1)

  if totalFrames <> cs.getFrameCount() Then
    msgText = "This animation requires " & totalFrames.ToString & _ 
      " frames to complete the marquee display. " 
    If totalFrames > cs.getFrameCount() Then 
      msgText = msgText & "Not enough frames exist in the 'Frames List' to generate a" & _
        " full rotation... OK to proceed?"
    Else
      msgText = msgText & "More frames exist in the 'Frames List' than are needed to" & _ 
        " generate a full rotation... OK to proceed?"
    End If

    response = System.Windows.Forms.MessageBox.Show (msgText, _
               "Marquee.VB Script", _
                System.Windows.Forms.MessageBoxButtons.OKCancel, _
                System.Windows.Forms.MessageBoxIcon.Exclamation) 
    If response = System.Windows.Forms.DialogResult.Cancel Then Exit Sub   
  End If  

' To create an animation occupying a predetermined number of frames, it may be necessary to 
' cycle the scrolling text around the LED more than once. Cause the marquee animation
' to be repeated 'Options.Cycles' numer of times. 

  For c = 1 to Options.Cycles

'   To implement the marquee animation, incrementally move the text raster pattern text 
'   foreward by one column about the perimeter of the cube and retain the pattern in
'   that position for 'Delay' number of frames (increasing the value of 'Delay' will 
'   slow the movement of the marquee effect).

    For i = 1 to L

      For dK = 0 To Options.Delay ' Repeat same raster text pattern for 'Delay' number of frames 

        If Options.Delay > 0 And Options.Decay = True Then 
          pctDecay = dK / Options.Delay
        End If

        I1 = 1.000 - pctDecay    ' primary intensity
        I2 = pctDecay            ' secondary intensity
        
'       Illuminate the LED background color according to the 'BackColor' option specified 

        If Options.Background <> "asis" Then
          r  = Options.BackColor.R ' red component of background color 
          g  = Options.BackColor.G ' green component of background color
          b  = Options.BackColor.B ' blue component of background color

          If Options.Background = "void" Then
            Options.BackColor.R = 0
            Options.BackColor.G = 0
            Options.BackColor.B = 0
            cs.drawCube (f, xMin, yMin, zMin, xMax, yMax, zMax, 0, 0, 0)
          ElseIf Options.Background = "fill" Then
            cs.drawCube (f, xMin, yMin, zMin, xMax, yMax, zMax, r, g, b)
          ElseIf Options.Background = "edge" Then
            cs.drawCube (f, xMin, yMin, zMin, xMax, yMin, zMax, r, g, b)
            cs.drawCube (f, xMin, yMin, zMin, xMin, yMax, zMax, r, g, b)
            cs.drawCube (f, xMax, yMin, zMin, xMax, yMax, zMax, r, g, b)
            cs.drawCube (f, xMin, yMax, zMin, xMax, yMax, zMax, r, g, b)
          End If
        Else ' Options.Background = "asis" 
          Options.BackColor.R = 0 ' red component of background color 
          Options.BackColor.G = 0 ' green component of background color
          Options.BackColor.B = 0 ' blue component of background color
        End If

'       Establish the text foreground colors according to the 'ForeColor' option specified 

        If Options.Foreground = "color" Then
          r = Options.ForeColor.R
          g = Options.ForeColor.G
          b = Options.ForeColor.B
        ElseIf Options.Foreground = "rainbow" Then
          Options.ForeColor.R = 0
          Options.ForeColor.G = 0
          Options.ForeColor.B = 0
        End If

'       Illuminate a portion of the raster pattern of text characters about the perimeter
'       of the cube 

        For zz = 0 to 7 ' each row in raster pattern
          z = zMax - zz ' cube row is inverse of pattern row

          For xx = 0 to xMax - 1 ' xx = column# in x-planes of cube 
            y = yMin

            If Line (zz).Substring (xx + i + xMax + 2 * yMax, 1) <> " " Then 
              x = xMax - xx - 1

              If Options.Foreground = "rainbow" Then 
                r = 255 * x / xMax
                g = 255 * y / yMax
                b = 255 * z / zMax
              End if

              If Line (zz).Substring (xx + i + 1 + xMax + 2 * yMax, 1) = " " Then
                rr = r * I1 + Options.BackColor.R * I2
                gg = g * I1 + Options.BackColor.G * I2
                bb = b * I1 + Options.BackColor.B * I2
                cs.drawVoxel (f, x, y, z, rr, gg, bb)
              Else
                cs.drawVoxel (f, x, y, z, r, g, b)
              End If

              If Line (zz).Substring (xx + i - 1 + xMax + 2 * yMax, 1) = " " Then
                If Options.Foreground = "rainbow" Then r = 255 * (x + 1) / xMax
                rr = r * I2 + Options.BackColor.R * I1
                gg = g * I2 + Options.BackColor.G * I1
                bb = b * I2 + Options.BackColor.B * I1
                cs.drawVoxel (f, x + 1, y, z, rr, gg, bb)              
              End If 
            End If
          Next ' For xx = 0 to xMax - 1
          
          y = yMax

          For xx = 0 to xMax - 1 ' xx = column# in x-planes of cube               
            If Line (zz).Substring (xx + i + yMax, 1) <> " " Then 
              x = xx + 1

              If Options.Foreground = "rainbow" Then
                r = 255 * x / xMax
                g = 255 * y / yMax
                b = 255 * z / zMax
              End if

              If Line (zz).Substring (xx + i + 1 + yMax, 1) = " " Then 
                rr = r * I1 + Options.BackColor.R * I2
                gg = g * I1 + Options.BackColor.G * I2
                bb = b * I1 + Options.BackColor.B * I2
                cs.drawVoxel (f, x, y, z, rr, gg, bb)
              Else 
                cs.drawVoxel (f, x, y, z, r, g, b)
              End If

              If Line (zz).Substring (xx + i - 1 + yMax, 1) = " " Then
                If Options.Foreground = "rainbow" Then r = 255 * (x - 1) / xMax
                rr = r * I2 + Options.BackColor.R * I1
                gg = g * I2 + Options.BackColor.G * I1
                bb = b * I2 + Options.BackColor.B * I1
                cs.drawVoxel (f, x - 1, y, z,  rr, gg, bb)
              End If              
            End If
          Next ' For xx = 0 to xMax - 1

          x = xMax

          For yy = 0 to yMax - 1 ' yy = column# in y-planes of cube 
            
            If Line (zz).Substring (yy + i + xMax + yMax, 1) <> " " Then 
              y = yMax - yy - 1

              If Options.Foreground = "rainbow" Then
                r = 255 * x / xMax
                g = 255 * y / yMax
                b = 255 * z / zMax
              End If

              If Line (zz).Substring (yy + i + 1 + xMax + yMax, 1) = " " Then
                rr = r * I1 + Options.BackColor.R * I2
                gg = g * I1 + Options.BackColor.G * I2
                bb = b * I1 + Options.BackColor.B * I2
                cs.drawVoxel (f, x, y, z, rr, gg, bb)
              Else
                 cs.drawVoxel (f, x, y, z, r, g, b)
              End If

              If Line (zz).Substring (yy + i - 1 + xMax + yMax, 1) = " " Then
                If Options.Foreground = "rainbow" Then g = 255 * (y + 1) / yMax
                rr = r * I2 + Options.BackColor.R * I1
                gg = g * I2 + Options.BackColor.G * I1
                bb = b * I2 + Options.BackColor.B * I1
                cs.drawVoxel (f, x, y + 1, z, rr, gg, bb)
              End If 
            End If
          Next ' For yy = 0 to yMax - 1 

          x = xMin
            
          For yy = 0 to yMax - 1 ' yy = column# in y-planes of cube 
            If Line (zz).Substring (yy + i, 1) <> " " Then
              y = yy + 1

              If Options.Foreground = "rainbow" Then
                r = 255 * x / xMax
                g = 255 * y / yMax
                b = 255 * z / zMax
              End If

              If Line (zz).Substring (yy + i + 1, 1) = " " Then
                rr = r * I1 + Options.BackColor.R * I2
                gg = g * I1 + Options.BackColor.G * I2
                bb = b * I1 + Options.BackColor.B * I2
                cs.drawVoxel (f, x, y, z, rr, gg, bb)
              Else
                cs.drawVoxel (f, x, y, z, r, g, b)
              End If

              If Line (zz).Substring (yy + i - 1, 1) = " " Then
                If Options.Foreground = "rainbow" Then b = 255 * (y - 1) / yMax
                rr = r * I2 + Options.BackColor.R * I1
                gg = g * I2 + Options.BackColor.G * I1
                bb = b * I2 + Options.BackColor.B * I1
                cs.drawVoxel (f, x, y - 1, z, rr, gg, bb)
              End If 
            End If  
          Next ' For yy = 0 to yMax - 1  
        Next ' For zz = 0 to 7 

        cs.showProgress(100 * f / (L * (Options.Delay + 1) * Options.Cycles)) 
        f = f + 1  	 

        If (cs.checkTermination() = true) Then Exit For 
  
      Next ' For dK = 0 To Options.Delay  
    Next ' For i = 1 to L 
  Next ' For c = 1 to Options.Cycles 

  L = L * Options.Cycles * (Options.Delay + 1) 
  frameCount = frameCount + 1
  
  System.Windows.Forms.MessageBox.Show ("Marquee display generation completed in " & _ 
                                        Math.Min (L, frameCount).ToString  & " frames.", _
                                        "Marquee.VB Script", _
                                        System.Windows.Forms.MessageBoxButtons.OK, _
                                        System.Windows.Forms.MessageBoxIcon.Asterisk)  	  
Catch ex as Exception
  System.Windows.Forms.MessageBox.Show (ex.ToString, _
                                        "Marquee.VB Script", _
                                        System.Windows.Forms.MessageBoxButtons.OK, _
                                        System.Windows.Forms.MessageBoxIcon.Stop)  	 

End Try

End Sub