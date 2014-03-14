#include <windows.h>
void DoEvents();
int Len(char des[]);
void sprintW(char des[],int sz,TCHAR src[]);
void addW(char * des,char * src);
void GetPathExe(char des[]);

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument,int nFunsterStil)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    WCHAR s[1024];
    char buffer[1024] = "";
    char buff[1024] = "";
    char exe[1024] = "";
    char path[1024] = "";
    char pathexe[1024] = "";
    char dirlib[1024] = "";
    char dirplugins[1024] = "";

    HMODULE hModule = GetModuleHandleW(NULL);

    GetModuleFileNameW(hModule, s, 1024);

    wsprintf(buffer, "%S", s); // a CAPITAL S
    sprintf(buff , "%s", lpszArgument); // a CAPITAL S

    GetPathExe(buffer);
    addW(path,buffer);
    addW(exe,path);
    
	if (buff[0] == 0){
		addW(exe,"/bin/QMaahad");
	}else{
		addW(exe,"/bin/Qpdate ");addW(exe,buff);
	}
	
    addW(dirlib,path); addW(dirlib,"/lib");
    addW(dirplugins,"QT_PLUGIN_PATH="); addW(dirplugins,path); addW(dirplugins,"/plugins");
    addW(pathexe,"PATH=%PATH%;"); addW(pathexe,dirlib);

    putenv(pathexe);
    putenv(dirplugins);

    ZeroMemory(&si,sizeof(si));
    si.cb=sizeof(si);
    ZeroMemory(&pi,sizeof(pi));
    CreateProcess(NULL,exe,NULL,NULL,0,0,NULL,NULL,&si,&pi);

    return 0;
}

void GetPathExe(char des[])
{
    int i=0;
    int sz=0;
    sz = Len(des);
    for(i=sz;i>0;i--){
        if (des[i] == '/' || des[i] == '\\') break;
        des[i] = '\0';
    }
    des[i] = '\0';
}
void sprintW(char des[],int sz,TCHAR src[])
{
    int i =0;
    for (i = 0;i<sz;i++){
        des[i]=src[i];
    }
}
void addW(char * des,char * src)
{
    int i = 0;
    int szdes = 0;
    int szsrc = 0;

    for (i = 0;;i++){
        if (des[i] == '\0'){szdes = i;break;}
    }
    for (i = 0;;i++){
        if (src[i] == '\0'){szsrc = i;break;}
    }
    for (i = 0;i < szsrc;i++){
        des[szdes+i]= src[i];
    }
}
int Len(char des[])
{
    int i = 0;
    int szdes = 0;
    for (i = 0;;i++){
        if (des[i] == '\0'){szdes = i;break;}
    }
    return szdes;
}


void DoEvents()
{
    MSG msg;
    BOOL result;
    while ( PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE ) )
    {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
    }
}
