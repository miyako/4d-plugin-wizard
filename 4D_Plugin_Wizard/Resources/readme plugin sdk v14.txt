Native drawing in v14.


V14 implement native drawing for plugin, to activate native draw you must use the plugin SDK v14. 

Native mode allow you to draw directly in CGContext/HDC using the system API.  

In native mode you are only allowed to draw during the eAE_Update and eAE_DesignUpdate

eAE_Update :

fMessage is a HDC on windows and a CGContextRef on OSX. 
The CGContext use reverted axis (quickdraw).


eAE_DesignUpdate

Windows : 
Plugin props . fWinHDC is HDC
Plugin props . fWinHWND is NULL
Plugin props . fMacWindow is NULL
Plugin props . fMacPort is NULL

OSX : 
Plugin props . fMacPort is a CGContextRef
Plugin props . fMacWindow is NULL
Plugin props . fWinHDC  is NULL
Plugin props . fWinHWND is NULL

Printing : 

Starting with 14.2 during eAE_PrintBand/eAE_GetPrintSize your plugin area will receive the printing context in fMessage


/******************************************************************************************************/
//  Helpers
/******************************************************************************************************/

Because graphic context is olny valid during update eAE_Update, we add PA_RedrawArea to allow to invalidate your external area.

Your can only call PA_RedrawArea from the plugin event loop. 

The following function can only be called during eAE_Update and eAE_DesignUpdate.


void PA_RedrawArea ( PA_PluginParameters params, char inNow,PA_Rect* inRect)

inNow 

If true invalidate the plugin area and then force update event. 
If false invalidate the plugin area and wait system update event

inRect
if NULL invalidate the whole area, else.....

PA_Rect	PA_GetAreaPortBounds( PA_PluginParameters params)
return the bounds of the graphic context hosting the plugin area. 
You will need this bounds if you want to change CGContext aixs

void PA_UseQuartzAxis( PA_PluginParameters params, short *outAreaX, short *outAreaY, short* outAreaWidth, short *outAreaHeight);
MAC Only 
Change the CGContext coordinate system to Quartz, and return the plugin area bounds in Quartz coordinate system
By default 4D works in Quickdraw coordinate system, you will need to switch to Quartz to draw text/picture, otherwise text/picture will be flipped


void PA_UseQuickdrawAxis( PA_PluginParameters params, short *outAreaX, short *outAreaY, short* outAreaWidth, short *outAreaHeight);
MAC Only
Change the CGContext coordinate system to QuickDraw, and return the plugin area bounds in QuickDraw coordinate system


/******************************************************************************************************/

The plugin rsr file is no longer mandatory in v14. 
To replace THM#,STR#,FONT#,VAR# we use a json file named manifest.json.
The manifest file must be placed inside the "contents" folder
  
 The syntax is simple, here is a description of json keys use in the 
 manifest
  
 Keys :

name -> plugin name
id -> plugin id (same as 4BNX)
commands-> is a array of commands
  
A command is described with 2 keys
theme -> the theme name. For easy writing, this value can be a xliff resname , 4D will resolve xliff when loading the plugin 
syntax -> the command syntax
  
compiler variables -> is a string array, same as VAR# & VAR<>
 
Here is a sample 
  

    "name": "test plugin",
    "id": 15000,
    "commands": [
        {
            "theme": "",
            "syntax": "_test External"
        },
  	{
             "theme": "testtheme1",
             "syntax": "command1(&L;&L):L"
         },
   	{
             "theme": "System Commands",
             "syntax": "command2(&L;&L):L"
        }
     ],
  "compiler variables": ["test_var:D","test_var1:L","<>test_var2:L"]
}

Constants (4DK#) can be define in XLIFF file, you can easily convert 4DK# to XLIFF with 4DPop Constant Editor