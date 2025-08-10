#include<easyx.h>
#include<fstream>
#include<iostream>//
#include <sstream>
#include <locale>
#include <Windows.h>
#include <mmsystem.h>
#include <string>
#include <vector>
#include <codecvt>
#include <conio.h>

#pragma comment (lib, "winmm.lib")
#pragma comment(lib, "Msimg32.lib")
using namespace std;
wstring stringToWstring(const string& str)
{
    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    wstring wstr(size, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size);
    return wstr;
}
void DrawAlphaBlueRect(int x, int y, int w, int h, BYTE alpha)
{
    HDC hdc = GetImageHDC(NULL); // EasyX主窗口HDC
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBmp = CreateCompatibleBitmap(hdc, w, h);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, memBmp);

    // 填充蓝色
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
    RECT rect = { 0, 0, w, h };
    FillRect(memDC, &rect, hBrush);
    DeleteObject(hBrush);

    // 设置混合参数
    BLENDFUNCTION bf = { AC_SRC_OVER, 0, alpha, 0 };
    AlphaBlend(hdc, x, y, w, h, memDC, 0, 0, w, h, bf);

    // 清理
    SelectObject(memDC, oldBmp);
    DeleteObject(memBmp);
    DeleteDC(memDC);
}
void DrawAlphaWhiteRect(int x, int y, int w, int h, BYTE alpha)
{
    HDC hdc = GetImageHDC(NULL); // EasyX主窗口HDC
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBmp = CreateCompatibleBitmap(hdc, w, h);
    HBITMAP oldBmp = (HBITMAP)SelectObject(memDC, memBmp);

    // 填充蓝色
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
    RECT rect = { 0, 0, w, h };
    FillRect(memDC, &rect, hBrush);
    DeleteObject(hBrush);

    // 设置混合参数
    BLENDFUNCTION bf = { AC_SRC_OVER, 0, alpha, 0 };
    AlphaBlend(hdc, x, y, w, h, memDC, 0, 0, w, h, bf);

    // 清理
    SelectObject(memDC, oldBmp);
    DeleteObject(memBmp);
    DeleteDC(memDC);
}
void DrawAlphaImage(IMAGE* image, int x, int y, BYTE alpha)
{
    HDC hdcDst = GetImageHDC(NULL);      // 目标（主窗口）HDC
    HDC hdcSrc = GetImageHDC(image);     // 源图片 HDC

    int w = image->getwidth();
    int h = image->getheight();

    BLENDFUNCTION bf = { AC_SRC_OVER, 0, alpha, 0 };
    AlphaBlend(hdcDst, x, y, w, h, hdcSrc, 0, 0, w, h, bf);
}
bool isPointInParallelogram(const POINT pts[4], POINT p)
{
    // 叉积法：点在四边形内，需在每条边的同侧
    int cross1 = (pts[1].x - pts[0].x) * (p.y - pts[0].y) - (pts[1].y - pts[0].y) * (p.x - pts[0].x);
    int cross2 = (pts[2].x - pts[1].x) * (p.y - pts[1].y) - (pts[2].y - pts[1].y) * (p.x - pts[1].x);
    int cross3 = (pts[3].x - pts[2].x) * (p.y - pts[2].y) - (pts[3].y - pts[2].y) * (p.x - pts[2].x);
    int cross4 = (pts[0].x - pts[3].x) * (p.y - pts[3].y) - (pts[0].y - pts[3].y) * (p.x - pts[3].x);

    // 全为正或全为负则在内部
    return (cross1 >= 0 && cross2 >= 0 && cross3 >= 0 && cross4 >= 0) ||  (cross1 <= 0 && cross2 <= 0 && cross3 <= 0 && cross4 <= 0);
}
class player
{
public:
    int math;
    int chinese;
	int english;
    int history;
    int geography;
    int politics;//道法
    int biology;//生物
    int chemistry;//化学
    int physics;//物理
	int computer;//计算机
	int pe;//体育
    wstring name;
    player(string panbieming)
    {
        if (panbieming != " ")
        {
            string fileadress="image/date/",line;
			fileadress += panbieming;
            fileadress += ".txt";
            wstring_convert<codecvt_utf8<wchar_t>> converter;
            fstream file(fileadress);
            file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));
			getline(file, line);
            int shangyici=0,dijige=0;
            for(int i = 0; i < line.length(); i++)
            {
                
                if (line[i] == ' ')
                {
                    string jicun = "";
                    switch (dijige)
                    {
                    case 0:
                        for (int j = shangyici; j < i; j++)
                            jicun += line[j];
						math = stoi(jicun);
                        break;
                    case 1:
                        for (int j = shangyici; j < i; j++)
                            jicun += line[j];
                        chinese = stoi(jicun);
                        break;
                    case 2:
                        for (int j = shangyici; j < i; j++)
                            jicun += line[j];
                        english = stoi(jicun);
                        break;
                    case 3:
                        for (int j = shangyici; j < i; j++)
                            jicun += line[j];
                        history = stoi(jicun);
                        break;
                    case 4:
                        for (int j = shangyici; j < i; j++)
                            jicun += line[j];
                        geography = stoi(jicun);
                        break;
                    case 5:
                        for (int j = shangyici; j < i; j++)
                            jicun += line[j];
                        politics = stoi(jicun);
                        break;
                    case 6:
                        for (int j = shangyici; j < i; j++)
                            jicun += line[j];
                        biology = stoi(jicun);
                        break;
                    case 7:
                        for (int j = shangyici; j < i; j++)
                            jicun += line[j];
                        chemistry = stoi(jicun);
                        break;
                    case 8:
                        for (int j = shangyici; j < i; j++)
                            jicun += line[j];
                        physics = stoi(jicun); 
                        break;
                    case 9:
                        for (int j = shangyici; j < i; j++)
                            jicun += line[j];
                        computer = stoi(jicun);
                        break;
                    case 10:
                        for (int j = shangyici; j < i; j++)
                            jicun += line[j];
                        pe = stoi(jicun);
                        break;
                    case 11:
                        for (int j = shangyici; j < i; j++)
                            jicun += line[j];
                        name = stringToWstring(jicun);
                        break;
                    default:
                        break;
                    }
					shangyici = i + 1;
                    dijige++;
                }
			}
            file.close();
        }

    }
    void attribute(wstring  whats, int yunsuanshu, bool isplus = 1)
    {
        if (whats == L"math")
            if (isplus)
                math += yunsuanshu;
            else
                math -= yunsuanshu;
        if (whats == L"chinese")
            if (isplus)
                chinese += yunsuanshu;
            else
                chinese -= yunsuanshu;
        if (whats == L"english")
            if (isplus)
                english += yunsuanshu;
            else
                english -= yunsuanshu;
        if (whats == L"politics")
            if (isplus)
                politics += yunsuanshu;
            else
                politics -= yunsuanshu;
        if (whats == L"history")
            if (isplus)
                history += yunsuanshu;
            else
                history -= yunsuanshu;
        if (whats == L"geography")
            if (isplus)
                geography += yunsuanshu;
            else
                geography -= yunsuanshu;
        if (whats == L"biology")
            if (isplus)
                biology += yunsuanshu;
            else
                biology -= yunsuanshu;
        if (whats == L"physics")
            if (isplus)
                physics += yunsuanshu;
            else
                physics -= yunsuanshu;
        if (whats == L"chemistry")
            if (isplus)
                chemistry += yunsuanshu;
            else
                chemistry -= yunsuanshu;
        if (whats == L"computer")
            if (isplus)
                computer += yunsuanshu;
            else
                computer -= yunsuanshu;
		if (whats == L"pe")
            if (isplus)
                pe += yunsuanshu;
            else
				pe -= yunsuanshu;
    }
    bool attribute2(wstring  whats, int yunsuanshu, bool isdayu = 1)
    {
        if (whats == L"math")
            if (isdayu)
                if(math  >= yunsuanshu)
                    return 1;
                else
                    return 0;
            else
                if (math <= yunsuanshu)
                    return 1;
                else
                    return 0;
        if (whats == L"chinese")
            if (isdayu)
                if (chinese >= yunsuanshu)
                    return 1;
                else
                    return 0;
            else
                if (chinese <= yunsuanshu)
                    return 1;
                else
                    return 0;
        if (whats == L"english")
            if (isdayu)
                if (english >= yunsuanshu)
                    return 1;
                else
                    return 0;
            else
                if (english <= yunsuanshu)
                    return 1;
                else
                    return 0;
        if (whats == L"politics")
            if (isdayu)
                if (politics >= yunsuanshu)
                    return 1;
                else
                    return 0;
            else
                if (politics <= yunsuanshu)
                    return 1;
                else
                    return 0;
        if (whats == L"history")
            if (isdayu)
                if (history >= yunsuanshu)
                    return 1;
                else
                    return 0;
            else
                if (history <= yunsuanshu)
                    return 1;
                else
                    return 0;
        if (whats == L"geography")
            if (isdayu)
                if (geography >= yunsuanshu)
                    return 1;
                else
                    return 0;
            else
                if (geography <= yunsuanshu)
                    return 1;
                else
                    return 0;
        if (whats == L"biology")
            if (isdayu)
                if (biology >= yunsuanshu)
                    return 1;
                else
                    return 0;
            else
                if (biology <= yunsuanshu)
                    return 1;
                else
                    return 0;
        if (whats == L"physics")
            if (isdayu)
                if (physics >= yunsuanshu)
                    return 1;
                else
                    return 0;
            else
                if (physics <= yunsuanshu)
                    return 1;
                else
                    return 0;
        if (whats == L"chemistry")
            if (isdayu)
                if (chemistry >= yunsuanshu)
                    return 1;
                else
                    return 0;
            else
                if (chemistry <= yunsuanshu)
                    return 1;
                else
                    return 0;
        if (whats == L"computer")
            if (isdayu)
                if (computer >= yunsuanshu)
                    return 1;
                else
                    return 0;
            else
                if (computer <= yunsuanshu)
                    return 1;
                else
                    return 0;
        if (whats == L"pe")
            if (isdayu)
                if (pe >= yunsuanshu)
                    return 1;
                else
                    return 0;
            else
                if (pe <= yunsuanshu)
                    return 1;
                else
                    return 0;
    }
}
self{"self"},
lihaoxuan{"lhx"},//程序代号lhx
lizhuoyang{ "lzy"},//程序代号lzy
zhaojionghe{ "zjh"},//程序代号zjh
bishujun{"bsj"};//程序代号bsj
wstring findTagtext( wstring input) 
{
	wstring willfind;   
    int fb, sb;
	int len = input.length();
	bool nfinds = 1;
    int findl = 0;
    for (int i = 0; i < len; i++)
    {
        if (nfinds && input[i] == '>')
        {
            fb = i + 1;
            nfinds = 0;
        }
        if (findl!=2&&input[i] == '<')
        {
            sb = i - 1;
            findl += 1;
        }
    }
    for(int i = fb; i <= sb; i++)
        willfind += input[i];
	return willfind;
}//提取标签内容
wstring findTagname(wstring input) 
{
	wstring willfind;
    for (int i = 1; 1; i++)
    {
        if(input[i]=='>')
			break;
		willfind += input[i];
    }
	return willfind;
}//提取标签名
wstring findTagltext(wstring input)
{
    wstring willfind;
    int lb;
    int len = input.length();
	int find = 0;
    for (int i = 0; i < len; i++)
    {
        if (input[i] == '>')
        {
            if (find == 2 && i == len - 1)
                return L"";
            if (find == 1)
            {
                lb = i + 1;
            }
            find++;
        }
    }
    for (int i = lb; i <= len-1; i++)
        willfind += input[i];
    return willfind;
}//提取标签尾部内容
void slow(wstring str)
{
    int  len2 = str.length() - 1;
    int x=100, y=402;
	ExMessage msg;
    int i{ 0 };
    BOOL isAlleady = {0};
    while (i <= len2 && (!isAlleady))
    {
        flushmessage();
        wstring stri;
        stri = str[i];
        if(x+13>700)
        {
            x = 100;
            y += 13;
            outtextxy(x, y, stri.c_str());
		}
        else
        {
            outtextxy(x, y, stri.c_str());
            x += 13;
        }
        Sleep(90);
        FlushBatchDraw();
        if (peekmessage(&msg, EX_KEY))//获得消息
        {
            FlushBatchDraw();
            for (int j = i + 1; j <= len2; j++)
            {
                wstring stri;
                stri = str[j];
                if (x + 13 > 700)
                {
                    x = 100;
                    y += 13;
                    outtextxy(x, y, stri.c_str());
                }
                else
                {
                    outtextxy(x, y, stri.c_str());
                    x += 13;
                }
                FlushBatchDraw();
            }
            isAlleady = 1;
        }
        i++;
    }
}
void getawait()
{
    wstring str=L"摁任意键继续！";
    outtextxy((800 - textwidth(str.c_str())), (600- textheight(str.c_str())), str.c_str());
    FlushBatchDraw();
    ExMessage msg;
    flushmessage();
	getmessage(&msg, EX_KEY );
    cleardevice();
}
/*cleardevice();
settextcolor(WHITE);
outtextxy(0, 0, L"我进来了！");
getawait();
switch (hnum)
{
case 1:
    putimage(300, 150, &player12, SRCAND);
    putimage(300, 150, &player11, SRCPAINT);
    break;
case 2:
    putimage(200, 150, &player12, SRCAND);
    putimage(200, 150, &player11, SRCPAINT);
    putimage(400, 150, &player22, SRCAND);
    putimage(400, 150, &player21, SRCPAINT);
    break;
case 3:
    putimage(100, 150, &player12, SRCAND);
    putimage(100, 150, &player11, SRCPAINT);
    putimage(300, 150, &player22, SRCAND);
    putimage(300, 150, &player21, SRCPAINT);
    putimage(500, 150, &player32, SRCAND);
    putimage(500, 150, &player31, SRCPAINT);
    break;
default:
    break;
}*/
void juqing(string name)
{
    initgraph(800, 600);
    cleardevice();
    IMAGE screen, textscreen;
    IMAGE player11, player21, player31;
    IMAGE player12, player22, player32;
    loadimage(&screen, _T("image/screen/classroom back.jpg"), 800, 600);
    wstring line;
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    wifstream file(name);
    file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));
    BeginBatchDraw();
    putimage(0, 0, &screen);
    FlushBatchDraw();
    //Sleep(3000);
    setbkmode(TRANSPARENT);
    wstring players = L"", lastname = L"";
    while (getline(file, line))
    {
        cleardevice();
        flushmessage();
        putimage(0, 0, &screen);

        int hnum = 0;
        player11.Resize(0, 0);
        player21.Resize(0, 0);
        player31.Resize(0, 0);
        player12.Resize(0, 0);
        player22.Resize(0, 0);
        player32.Resize(0, 0);
        for (int i = 0; i < players.length(); i++)
        {
            if (players[i] == L' ')
            {
                wstring linshijicun1 = L"image/player/", linshijicun2;
                for (int j = i + 1; players[j] != L' ' && j < players.length(); j++)
                    linshijicun1 += players[j];
                linshijicun2 = linshijicun1;
                linshijicun1 += L"1.jpg";
                linshijicun2 += L"2.jpg";
                hnum++;
                if (hnum == 1)
                {
                    loadimage(&player11, linshijicun1.c_str(), 200, 366);
                    loadimage(&player12, linshijicun2.c_str(), 200, 366);
                }
                if (hnum == 2)
                {
                    loadimage(&player21, linshijicun1.c_str(), 200, 366);
                    loadimage(&player22, linshijicun2.c_str(), 200, 366);
                }
                if (hnum == 3)
                {
                    loadimage(&player31, linshijicun1.c_str(), 200, 366);
                    loadimage(&player32, linshijicun2.c_str(), 200, 366);
                }

            }
        }

        if (line[0] == '<')
        {
            wstring thetagname = findTagname(line);
            if (thetagname == L"button")
            {
                wstring thetagtext = findTagtext(line);
                wstring thefb, thesb;
                bool theone = 1;
                int howwlong = thetagtext.length() - 1;
                for (int j = 0; j <= howwlong; j++)
                {
                    if (thetagtext[j] == ' ')
                    {
                        for (int k = 0; k < j; k++)
                            thefb += thetagtext[k];
                        for (int k = j + 1; k <= howwlong; k++)
                            thesb += thetagtext[k];
                        theone = 0;
                        bool isbutton2out = 0;
                        for (int k = 0; k <= howwlong; k++)
                        {
                            if (thesb[k] == L'/')
                            {
                                int thefindlen = thesb.length();
                                wstring palyer, whats, yunsuanshu;
                                int  num = 0;//yunsuanshu是运算数，num是运算符
                                bool isdayu = 1;
                                for (int j = k; num <= 3 && j < thefindlen; j++)
                                {
                                    if (thesb[j] == '/')
                                        num++;
                                    if (thesb[j] != '+' && thesb[j] != '-' && thesb[j] != '/' && num == 1)
                                        palyer += thesb[j];
                                    if (thesb[j] != '+' && thesb[j] != '-' && thesb[j] != '/' && num == 2)
                                        whats += thesb[j];
                                    if ((thesb[j] == '+' || thesb[j] == '-') && thesb[j] != '/' && num == 3)
                                        if (thesb[j] == '+')
                                            isdayu = 0;
                                    if (thesb[j] != '+' && thesb[j] != '-' && thesb[j] != '/' && num == 3)
                                        yunsuanshu += thesb[j];
                                }
                                if (palyer == L"lhx")
                                    if (lihaoxuan.attribute2(whats, stoi(yunsuanshu), isdayu))
                                        isbutton2out = 1;
                                if (palyer == L"lzy")
                                    if (lizhuoyang.attribute2(whats, stoi(yunsuanshu), isdayu))
                                        isbutton2out = 1;
                                if (palyer == L"zjh")
                                    if (zhaojionghe.attribute2(whats, stoi(yunsuanshu), isdayu))
                                        isbutton2out = 1;
                                if (palyer == L"bsj")
                                    if (bishujun.attribute2(whats, stoi(yunsuanshu), isdayu))
                                        isbutton2out = 1;
                                if (palyer == L"self")
                                    if (self.attribute2(whats, stoi(yunsuanshu), isdayu))
                                        isbutton2out = 1;
                                wstring thefb2;
                                for (int l = 0; l < k; l++)
                                    thefb2 += thesb[l];
                                thesb = thefb2;
                                break;
                            }

                        }
                        ExMessage msg;
                        bool fisMouseRightDown = 1;
                        bool where = 0;
                        int howfblong = textwidth(thefb.c_str()), howsblong = textwidth(thesb.c_str());
                        int howfbtall = textheight(thefb.c_str()), howsbtall = textheight(thesb.c_str());
                        while (fisMouseRightDown)
                        {
                            cleardevice();
                            putimage(0, 0, &screen);
                            switch (hnum)
                            {
                            case 1:
                                putimage(300, 150, &player12, SRCAND);
                                putimage(300, 150, &player11, SRCPAINT);
                                break;
                            case 2:
                                putimage(200, 150, &player12, SRCAND);
                                putimage(200, 150, &player11, SRCPAINT);
                                putimage(400, 150, &player22, SRCAND);
                                putimage(400, 150, &player21, SRCPAINT);
                                break;
                            case 3:
                                putimage(100, 150, &player12, SRCAND);
                                putimage(100, 150, &player11, SRCPAINT);
                                putimage(300, 150, &player22, SRCAND);
                                putimage(300, 150, &player21, SRCPAINT);
                                putimage(500, 150, &player32, SRCAND);
                                putimage(500, 150, &player31, SRCPAINT);
                                break;

                            default:
                                break;
                            }
                            DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                            if (!where)
                            {
                                setfillcolor(YELLOW);
                                fillrectangle(20, 190, 780, 210 + howfbtall);//((800 - howfblong) / 2) - 10,(800 - ((800 - howfblong) / 2)) + 10
                                if (isbutton2out)
                                {
                                    setfillcolor(WHITE);
                                    fillrectangle(20, 230 + howfbtall, 780, 250 + howfbtall + howsbtall);
                                }
                            }
                            else
                            {
                                setfillcolor(WHITE);
                                fillrectangle(20, 190, 780, 210 + howfbtall);//((800 - howfblong) / 2) - 10,(800 - ((800 - howfblong) / 2)) + 10
                                if (isbutton2out)
                                {
                                    setfillcolor(YELLOW);
                                    fillrectangle(20, 230 + howfbtall, 780, 250 + howfbtall + howsbtall);//((800 - howsblong) / 2) - 10,(800 - ((800 - howsblong) / 2)) + 10
                                }
                            }
                            settextcolor(BLACK);
                            outtextxy((800 - howfblong) / 2, 200, thefb.c_str());
                            if (isbutton2out)
                                outtextxy((800 - howsblong) / 2, 240 + howfbtall, thesb.c_str());
                            FlushBatchDraw();
                            while (peekmessage(&msg, EX_MOUSE))//获得消息
                            {
                                if (msg.message == WM_LBUTTONDOWN && msg.x >= 20 && msg.x <= 780 && msg.y >= 190 && msg.y <= 210 + howfbtall)
                                {
                                    fisMouseRightDown = 0;
                                    wstring theltext = findTagltext(line);
                                    if (theltext != L"")
                                    {
                                        wstring  thefind;
                                        int theltextleng = theltext.length();
                                        for (int i = 0; i < theltextleng; i++)
                                            if (theltext[i] == ' ')
                                                for (int j = 0; j < i; j++)
                                                    thefind += theltext[j];
                                        /*cleardevice();
                                        putimage(0, 0, &screen);
                                        slow(thefind);*/
                                        int thefindlen = thefind.length();
                                        bool isout = 0;
                                        for (int i = 0; i < thefindlen; i++)
                                        {
                                            if (thefind[i] == '<')
                                            {

                                                isout = 1;
                                                wstring thetagname;
                                                for (int j = i + 1; j < thefindlen; j++)
                                                {
                                                    if (thefind[j] == '>')
                                                        break;
                                                    thetagname += thefind[j];
                                                }
                                                if (thetagname == L"turnto")
                                                {
                                                    string theturnto="";
                                                    wstring reallyout;
                                                    for (int j = i + 8; thefind[j] != L' ' && thefind[j] != L'<' && j < thefindlen; j++)
                                                        theturnto += thefind[j];
                                                    for (int j = 0; thefind[j] != L'<' && j < thefindlen; j++)
                                                        reallyout+= thefind[j];
                                                    cleardevice();
                                                    juqing(theturnto);
                                                    cleardevice();
                                                }
                                                else if (thetagname == L"load")
                                                {
                                                    int num = 0;
                                                    wstring theloadname = L"", theloaddress = L"image/prop/", reallyout;
                                                    for (int j = 0; thefind[j] != L'<' && j < thefindlen; j++)
                                                        reallyout += thefind[j];
                                                    IMAGE theload;
                                                    for (int j = i + 6; num <= 4 && j < thefindlen; j++)
                                                    {
                                                        if (thefind[j] == '/')
                                                            num++;
                                                        if (num == 1)
                                                            theloadname += thefind[j];
                                                        if (num == 3)
                                                            theloaddress += thefind[j];
                                                    }
                                                    loadimage(&theload, theloaddress.c_str(), 200, 200);
                                                    cleardevice();
                                                    putimage(0, 0, &screen);
                                                    switch (hnum)
                                                    {
                                                    case 1:
                                                        putimage(300, 150, &player12, SRCAND);
                                                        putimage(300, 150, &player11, SRCPAINT);
                                                        break;
                                                    case 2:
                                                        putimage(200, 150, &player12, SRCAND);
                                                        putimage(200, 150, &player11, SRCPAINT);
                                                        putimage(400, 150, &player22, SRCAND);
                                                        putimage(400, 150, &player21, SRCPAINT);
                                                        break;
                                                    case 3:
                                                        putimage(100, 150, &player12, SRCAND);
                                                        putimage(100, 150, &player11, SRCPAINT);
                                                        putimage(300, 150, &player22, SRCAND);
                                                        putimage(300, 150, &player21, SRCPAINT);
                                                        putimage(500, 150, &player32, SRCAND);
                                                        putimage(500, 150, &player31, SRCPAINT);
                                                        break;

                                                    default:
                                                        break;
                                                    }
                                                    DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                                                    if (reallyout != L"")
                                                    {
                                                        slow(reallyout);
                                                        getawait();
                                                    }
                                                    cleardevice();
                                                    putimage(0, 0, &screen);
                                                    switch (hnum)
                                                    {
                                                    case 1:
                                                        putimage(300, 150, &player12, SRCAND);
                                                        putimage(300, 150, &player11, SRCPAINT);
                                                        break;
                                                    case 2:
                                                        putimage(200, 150, &player12, SRCAND);
                                                        putimage(200, 150, &player11, SRCPAINT);
                                                        putimage(400, 150, &player22, SRCAND);
                                                        putimage(400, 150, &player21, SRCPAINT);
                                                        break;
                                                    case 3:
                                                        putimage(100, 150, &player12, SRCAND);
                                                        putimage(100, 150, &player11, SRCPAINT);
                                                        putimage(300, 150, &player22, SRCAND);
                                                        putimage(300, 150, &player21, SRCPAINT);
                                                        putimage(500, 150, &player32, SRCAND);
                                                        putimage(500, 150, &player31, SRCPAINT);
                                                        break;

                                                    default:
                                                        break;
                                                    }
                                                    DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                                                    putimage(300, 100, &theload);
                                                    slow(L"恭喜获得：" + theloadname);
                                                    getawait();
                                                }
                                                else if (thetagname == L"attribute")
                                                {
                                                    wstring palyer, whats, reallyout, yunsuanshu;
                                                    int  num = 0;//yunsuanshu是运算数，num是运算符
                                                    bool isplus = 1;
                                                    for (int j = i + 11; num <= 2 && j < thefindlen; j++)
                                                    {
                                                        if (thefind[j] == '/')
                                                            num++;
                                                        if (thefind[j] != '+' && thefind[j] != '-' && thefind[j] != '/' && num == 0)
                                                            palyer += thefind[j];
                                                        if (thefind[j] != '+' && thefind[j] != '-' && thefind[j] != '/' && num == 1)
                                                            whats += thefind[j];
                                                        if ((thefind[j] == '+' || thefind[j] == '-') && thefind[j] != '/' && num == 2)
                                                            if (thefind[j] == '-')
                                                                isplus = 0;
                                                        if (thefind[j] != '+' && thefind[j] != '-' && thefind[j] != '/' && num == 2)
                                                            yunsuanshu += thefind[j];

                                                    }
                                                    if (palyer == L"lhx")
                                                        lihaoxuan.attribute(whats, stoi(yunsuanshu), isplus);
                                                    if (palyer == L"lzy")
                                                        lizhuoyang.attribute(whats, stoi(yunsuanshu), isplus);
                                                    if (palyer == L"zjh")
                                                        zhaojionghe.attribute(whats, stoi(yunsuanshu), isplus);
                                                    if (palyer == L"bsj")
                                                        bishujun.attribute(whats, stoi(yunsuanshu), isplus);
                                                    if (palyer == L"self")
                                                        self.attribute(whats, stoi(yunsuanshu), isplus);
                                                }
                                            }
                                        }
                                        if (!isout)
                                        {
                                            cleardevice();
                                            putimage(0, 0, &screen);
                                            switch (hnum)
                                            {
                                            case 1:
                                                putimage(300, 150, &player12, SRCAND);
                                                putimage(300, 150, &player11, SRCPAINT);
                                                break;
                                            case 2:
                                                putimage(200, 150, &player12, SRCAND);
                                                putimage(200, 150, &player11, SRCPAINT);
                                                putimage(400, 150, &player22, SRCAND);
                                                putimage(400, 150, &player21, SRCPAINT);
                                                break;
                                            case 3:
                                                putimage(100, 150, &player12, SRCAND);
                                                putimage(100, 150, &player11, SRCPAINT);
                                                putimage(300, 150, &player22, SRCAND);
                                                putimage(300, 150, &player21, SRCPAINT);
                                                putimage(500, 150, &player32, SRCAND);
                                                putimage(500, 150, &player31, SRCPAINT);
                                                break;

                                            default:
                                                break;
                                            }
                                            DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                                            slow(thefind);
                                            getawait();
                                        }
                                    }
                                }
                                if (msg.message == WM_LBUTTONDOWN && msg.x >= 20 && msg.x <= 780 && msg.y >= 230 + howfbtall && msg.y <= 250 + howfbtall + howsbtall && isbutton2out)
                                {
                                    fisMouseRightDown = 0;
                                    wstring theltext = findTagltext(line);
                                    if (findTagltext(line) != L"")
                                    {
                                        wstring  thefind;
                                        int theltextleng = theltext.length();
                                        for (int i = 0; i < theltextleng; i++)
                                            if (theltext[i] == ' ')
                                                for (int j = i + 1; j < theltextleng; j++)
                                                    thefind += theltext[j];
                                        /*cleardevice();
                                        putimage(0, 0, &screen);
                                        slow(thefind);*/
                                        int thefindlen = thefind.length();
                                        bool isout = 0;
                                        for (int i = 0; i < thefindlen; i++)
                                        {
                                            if (thefind[i] == '<')
                                            {

                                                isout = 1;
                                                wstring thetagname;
                                                for (int j = i + 1; j < thefindlen; j++)
                                                {
                                                    if (thefind[j] == '>')
                                                        break;
                                                    thetagname += thefind[j];
                                                }
                                                if (thetagname == L"turnto")
                                                {
                                                    string theturnto = "";
                                                    wstring reallyout;
                                                    for (int j = i + 8; thefind[j] != L' ' && thefind[j] != L'<' && j < thefindlen; j++)
                                                        theturnto += thefind[j];
                                                    for (int j = 0; thefind[j] != L'<' && j < thefindlen; j++)
                                                        reallyout += thefind[j];
                                                    cleardevice();
                                                    juqing(theturnto);
                                                    cleardevice();
                                                }
                                                else if (thetagname == L"load")
                                                {
                                                    int num = 0;
                                                    wstring theloadname = L"", theloaddress = L"image/prop/", reallyout;
                                                    for (int j = 0; thefind[j] != L'<' && j < thefindlen; j++)
                                                        reallyout += thefind[j];
                                                    IMAGE theload;
                                                    for (int j = i + 6; num <= 4 && j < thefindlen; j++)
                                                    {
                                                        if (thefind[j] == '/')
                                                            num++;
                                                        if (num == 1)
                                                            theloadname += thefind[j];
                                                        if (num == 3)
                                                            theloaddress += thefind[j];
                                                    }
                                                    loadimage(&theload, theloaddress.c_str(), 200, 200);
                                                    cleardevice();
                                                    putimage(0, 0, &screen);
                                                    switch (hnum)
                                                    {
                                                    case 1:
                                                        putimage(300, 150, &player12, SRCAND);
                                                        putimage(300, 150, &player11, SRCPAINT);
                                                        break;
                                                    case 2:
                                                        putimage(200, 150, &player12, SRCAND);
                                                        putimage(200, 150, &player11, SRCPAINT);
                                                        putimage(400, 150, &player22, SRCAND);
                                                        putimage(400, 150, &player21, SRCPAINT);
                                                        break;
                                                    case 3:
                                                        putimage(100, 150, &player12, SRCAND);
                                                        putimage(100, 150, &player11, SRCPAINT);
                                                        putimage(300, 150, &player22, SRCAND);
                                                        putimage(300, 150, &player21, SRCPAINT);
                                                        putimage(500, 150, &player32, SRCAND);
                                                        putimage(500, 150, &player31, SRCPAINT);
                                                        break;

                                                    default:
                                                        break;
                                                    }
                                                    DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                                                    if (reallyout != L"")
                                                    {
                                                        slow(reallyout);
                                                        getawait();
                                                    }
                                                    cleardevice();
                                                    putimage(0, 0, &screen);
                                                    switch (hnum)
                                                    {
                                                    case 1:
                                                        putimage(300, 150, &player12, SRCAND);
                                                        putimage(300, 150, &player11, SRCPAINT);
                                                        break;
                                                    case 2:
                                                        putimage(200, 150, &player12, SRCAND);
                                                        putimage(200, 150, &player11, SRCPAINT);
                                                        putimage(400, 150, &player22, SRCAND);
                                                        putimage(400, 150, &player21, SRCPAINT);
                                                        break;
                                                    case 3:
                                                        putimage(100, 150, &player12, SRCAND);
                                                        putimage(100, 150, &player11, SRCPAINT);
                                                        putimage(300, 150, &player22, SRCAND);
                                                        putimage(300, 150, &player21, SRCPAINT);
                                                        putimage(500, 150, &player32, SRCAND);
                                                        putimage(500, 150, &player31, SRCPAINT);
                                                        break;

                                                    default:
                                                        break;
                                                    }
                                                    DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                                                    putimage(300, 100, &theload);
                                                    slow(L"恭喜获得：" + theloadname);
                                                    getawait();
                                                }
                                                else if (thetagname == L"attribute")
                                                {
                                                    wstring palyer, whats, reallyout, yunsuanshu;
                                                    int  num = 0;//yunsuanshu是运算数，num是运算符
                                                    bool isplus = 1;
                                                    for (int j = i + 11; num <= 2 && j < thefindlen; j++)
                                                    {
                                                        if (thefind[j] == '/')
                                                            num++;
                                                        if (thefind[j] != '+' && thefind[j] != '-' && thefind[j] != '/' && num == 0)
                                                            palyer += thefind[j];
                                                        if (thefind[j] != '+' && thefind[j] != '-' && thefind[j] != '/' && num == 1)
                                                            whats += thefind[j];
                                                        if ((thefind[j] == '+' || thefind[j] == '-') && thefind[j] != '/' && num == 2)
                                                            if (thefind[j] == '-')
                                                                isplus = 0;
                                                        if (thefind[j] != '+' && thefind[j] != '-' && thefind[j] != '/' && num == 2)
                                                            yunsuanshu += thefind[j];

                                                    }
                                                    if (palyer == L"lhx")
                                                        lihaoxuan.attribute(whats, stoi(yunsuanshu), isplus);
                                                    if (palyer == L"lzy")
                                                        lizhuoyang.attribute(whats, stoi(yunsuanshu), isplus);
                                                    if (palyer == L"zjh")
                                                        zhaojionghe.attribute(whats, stoi(yunsuanshu), isplus);
                                                    if (palyer == L"bsj")
                                                        bishujun.attribute(whats, stoi(yunsuanshu), isplus);
                                                    if (palyer == L"self")
                                                        self.attribute(whats, stoi(yunsuanshu), isplus);
                                                }
                                            }
                                        }
                                        if (!isout)
                                        {
                                            cleardevice();
                                            putimage(0, 0, &screen);
                                            switch (hnum)
                                            {
                                            case 1:
                                                putimage(300, 150, &player12, SRCAND);
                                                putimage(300, 150, &player11, SRCPAINT);
                                                break;
                                            case 2:
                                                putimage(200, 150, &player12, SRCAND);
                                                putimage(200, 150, &player11, SRCPAINT);
                                                putimage(400, 150, &player22, SRCAND);
                                                putimage(400, 150, &player21, SRCPAINT);
                                                break;
                                            case 3:
                                                putimage(100, 150, &player12, SRCAND);
                                                putimage(100, 150, &player11, SRCPAINT);
                                                putimage(300, 150, &player22, SRCAND);
                                                putimage(300, 150, &player21, SRCPAINT);
                                                putimage(500, 150, &player32, SRCAND);
                                                putimage(500, 150, &player31, SRCPAINT);
                                                break;

                                            default:
                                                break;
                                            }
                                            DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                                            slow(thefind);
                                            getawait();
                                        }
                                    }
                                }
                                if (msg.x >= 20 && msg.x <= 780 && msg.y >= 190 && msg.y <= 210 + howfbtall)
                                    where = 0;
                                if (msg.x >= 20 && msg.x <= 780 && msg.y >= 230 + howfbtall && msg.y <= 240 + howfbtall && isbutton2out)
                                    where = 1;

                            }
                        }
                        break;
                    }
                }
                if (theone)
                {
                    wstring thetagtext = findTagtext(line);
                    thefb = thetagtext;
                    ExMessage msg;
                    bool fisMouseRightDown = 1;
                    int howfblong = textwidth(thefb.c_str());
                    int howfbtall = textheight(thefb.c_str());
                    while (fisMouseRightDown)
                    {
                        cleardevice();
                        putimage(0, 0, &screen);
                        switch (hnum)
                        {
                        case 1:
                            putimage(300, 150, &player12, SRCAND);
                            putimage(300, 150, &player11, SRCPAINT);
                            break;
                        case 2:
                            putimage(200, 150, &player12, SRCAND);
                            putimage(200, 150, &player11, SRCPAINT);
                            putimage(400, 150, &player22, SRCAND);
                            putimage(400, 150, &player21, SRCPAINT);
                            break;
                        case 3:
                            putimage(100, 150, &player12, SRCAND);
                            putimage(100, 150, &player11, SRCPAINT);
                            putimage(300, 150, &player22, SRCAND);
                            putimage(300, 150, &player21, SRCPAINT);
                            putimage(500, 150, &player32, SRCAND);
                            putimage(500, 150, &player31, SRCPAINT);
                            break;

                        default:
                            break;
                        }
                        DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                        setfillcolor(YELLOW);
                        fillrectangle(20, 190, 780, 210 + howfbtall);
                        settextcolor(BLACK);
                        outtextxy((800 - howfblong) / 2, 200, thefb.c_str());
                        FlushBatchDraw();
                        while (peekmessage(&msg, EX_MOUSE))//获得消息
                        {
                            if (msg.message == WM_LBUTTONDOWN && msg.x >= 20 && msg.x <= 780 && msg.y >= 190 && msg.y <= 210 + howfbtall)
                            {
                                fisMouseRightDown = 0;
                                if (findTagltext(line) != L"")
                                {
                                    wstring theltext = findTagltext(line);
                                    int theltextleng = theltext.length();
                                    wstring  thefind = theltext;
                                    /*cleardevice();
                                    putimage(0, 0, &screen);
                                    slow(thefind);*/
                                    int thefindlen = thefind.length();
                                    bool isout = 0;
                                    for (int i = 0; i < thefindlen; i++)
                                    {
                                        if (thefind[i] == '<')
                                        {

                                            isout = 1;
                                            wstring thetagname;
                                            for (int j = i + 1; j < thefindlen; j++)
                                            {
                                                if (thefind[j] == '>')
                                                    break;
                                                thetagname += thefind[j];
                                            }
                                            if (thetagname == L"turnto")
                                            {
                                                string theturnto = "";
                                                wstring reallyout;
                                                for (int j = i + 8; thefind[j] != L' ' && thefind[j] != L'<' && j < thefindlen; j++)
                                                    theturnto += thefind[j];
                                                for (int j = 0; thefind[j] != L'<' && j < thefindlen; j++)
                                                    reallyout += thefind[j];
                                                cleardevice();
                                                juqing(theturnto);
                                                cleardevice();
                                            }
                                            else if (thetagname == L"load")
                                            {
                                                int num = 0;
                                                wstring theloadname = L"", theloaddress = L"image/prop/", reallyout;
                                                for (int j = 0; thefind[j] != L'<' && j < thefindlen; j++)
                                                    reallyout += thefind[j];
                                                IMAGE theload;
                                                for (int j = i + 6; num <= 4 && j < thefindlen; j++)
                                                {
                                                    if (thefind[j] == '/')
                                                        num++;
                                                    if (num == 1)
                                                        theloadname += thefind[j];
                                                    if (num == 3)
                                                        theloaddress += thefind[j];
                                                }
                                                loadimage(&theload, theloaddress.c_str(), 200, 200);
                                                cleardevice();
                                                putimage(0, 0, &screen);
                                                if (reallyout != L"")
                                                {
                                                    slow(reallyout);
                                                    getawait();
                                                }
                                                cleardevice();
                                                putimage(0, 0, &screen);
                                                switch (hnum)
                                                {
                                                case 1:
                                                    putimage(300, 150, &player12, SRCAND);
                                                    putimage(300, 150, &player11, SRCPAINT);
                                                    break;
                                                case 2:
                                                    putimage(200, 150, &player12, SRCAND);
                                                    putimage(200, 150, &player11, SRCPAINT);
                                                    putimage(400, 150, &player22, SRCAND);
                                                    putimage(400, 150, &player21, SRCPAINT);
                                                    break;
                                                case 3:
                                                    putimage(100, 150, &player12, SRCAND);
                                                    putimage(100, 150, &player11, SRCPAINT);
                                                    putimage(300, 150, &player22, SRCAND);
                                                    putimage(300, 150, &player21, SRCPAINT);
                                                    putimage(500, 150, &player32, SRCAND);
                                                    putimage(500, 150, &player31, SRCPAINT);
                                                    break;

                                                default:
                                                    break;
                                                }
                                                DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                                                putimage(300, 100, &theload);
                                                slow(L"恭喜获得：" + theloadname);
                                                getawait();
                                            }
                                            else if (thetagname == L"attribute")
                                            {
                                                wstring palyer, whats, reallyout, yunsuanshu;
                                                int  num = 0;//yunsuanshu是运算数，num是运算符
                                                bool isplus = 1;
                                                for (int j = i + 11; num <= 2 && j < thefindlen; j++)
                                                {
                                                    if (thefind[j] == '/')
                                                        num++;
                                                    if (thefind[j] != '+' && thefind[j] != '-' && thefind[j] != '/' && num == 0)
                                                        palyer += thefind[j];
                                                    if (thefind[j] != '+' && thefind[j] != '-' && thefind[j] != '/' && num == 1)
                                                        whats += thefind[j];
                                                    if ((thefind[j] == '+' || thefind[j] == '-') && thefind[j] != '/' && num == 2)
                                                        if (thefind[j] == '-')
                                                            isplus = 0;
                                                    if (thefind[j] != '+' && thefind[j] != '-' && thefind[j] != '/' && num == 2)
                                                        yunsuanshu += thefind[j];

                                                }
                                                if (palyer == L"lhx")
                                                    lihaoxuan.attribute(whats, stoi(yunsuanshu), isplus);
                                                if (palyer == L"lzy")
                                                    lizhuoyang.attribute(whats, stoi(yunsuanshu), isplus);
                                                if (palyer == L"zjh")
                                                    zhaojionghe.attribute(whats, stoi(yunsuanshu), isplus);
                                                if (palyer == L"bsj")
                                                    bishujun.attribute(whats, stoi(yunsuanshu), isplus);
                                                if (palyer == L"self")
                                                    self.attribute(whats, stoi(yunsuanshu), isplus);
                                            }
                                        }
                                    }
                                    if (!isout)
                                    {
                                        cleardevice();
                                        putimage(0, 0, &screen);
                                        switch (hnum)
                                        {
                                        case 1:
                                            putimage(300, 150, &player12, SRCAND);
                                            putimage(300, 150, &player11, SRCPAINT);
                                            break;
                                        case 2:
                                            putimage(200, 150, &player12, SRCAND);
                                            putimage(200, 150, &player11, SRCPAINT);
                                            putimage(400, 150, &player22, SRCAND);
                                            putimage(400, 150, &player21, SRCPAINT);
                                            break;
                                        case 3:
                                            putimage(100, 150, &player12, SRCAND);
                                            putimage(100, 150, &player11, SRCPAINT);
                                            putimage(300, 150, &player22, SRCAND);
                                            putimage(300, 150, &player21, SRCPAINT);
                                            putimage(500, 150, &player32, SRCAND);
                                            putimage(500, 150, &player31, SRCPAINT);
                                            break;

                                        default:
                                            break;
                                        }
                                        DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                                        slow(thefind);
                                        getawait();
                                    }
                                }
                            }
                        }
                    }
                }

            }
            if (thetagname == L"player")
            {

                wstring thetagtext = findTagtext(line);
                wstring caozuo, player = L" ";
                for (int i = 0; i < thetagtext.length(); i++)
                    if (thetagtext[i] == ' ')
                    {
                        for (int j = 0; j < i; j++)
                            caozuo += thetagtext[j];
                        for (int j = i + 1; j < thetagtext.length(); j++)
                            player += thetagtext[j];
                    }
                if (caozuo == L"load")
                {
                    players += player;
                    hnum++;
                    for (int i = 0; i < player.length(); i++)
                    {
                        if (player[i] == L' ')
                        {
                            wstring linshijicun1 = L"image/player/", linshijicun2, nowname;
                            for (int j = i + 1; player[j] != L' ' && j < player.length(); j++)
                            {
                                nowname += player[j];
                                linshijicun1 += player[j];
                            }
                            if (nowname == L"lhx")
                            {
                                lastname += L"&&";
                                lastname += L"李皓轩";
                            }
                            else if (nowname == L"lzy")
                            {
                                lastname += L"&&";
                                lastname += L"李卓阳";
                            }
                            else if (nowname == L"zjh")
                            {
                                //lastname += L"&&";
                                lastname += L"&&赵炯赫";
                            }
                            else if (nowname == L"bsj")
                            {
                                lastname += L"&&";
                                lastname += L"毕书俊";
                            }
                            else if (nowname != L"bsj" && nowname != L"lhx" && nowname != L"lzy" && nowname != L"zjh")
                            {
                                lastname += L"&&";
                                lastname += L"NPC";
                            }
                            linshijicun2 = linshijicun1;
                            linshijicun1 += L"1.jpg";
                            linshijicun2 += L"2.jpg";
                            if (hnum == 1)
                            {
                                loadimage(&player11, linshijicun1.c_str(), 200, 366);
                                loadimage(&player12, linshijicun2.c_str(), 200, 366);
                            }
                            if (hnum == 2)
                            {
                                loadimage(&player21, linshijicun1.c_str(), 200, 366);
                                loadimage(&player22, linshijicun2.c_str(), 200, 366);
                            }
                            if (hnum == 3)
                            {
                                loadimage(&player31, linshijicun1.c_str(), 200, 366);
                                loadimage(&player32, linshijicun2.c_str(), 200, 366);
                            }
                            break;
                        }
                    }
                    if (hnum - 1 == 1)
                    {
                        int x1 = 300;
                        int x2 = 800;
                        for (; x1 >= 200; x1 -= 10, x2 -= 40)
                        {
                            cleardevice();
                            putimage(0, 0, &screen);
                            putimage(x1, 150, &player12, SRCAND);
                            putimage(x1, 150, &player11, SRCPAINT);
                            putimage(x2, 150, &player22, SRCAND);
                            putimage(x2, 150, &player21, SRCPAINT);
                            DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                            FlushBatchDraw();
                            Sleep(10);
                        }
                    }
                    if (hnum - 1 == 2)
                    {
                        int x1 = 200; int x2 = 400; int x3 = 800;
                        for (; x1 >= 100; x1 -= 10, x2 -= 10, x3 -= 20)
                        {
                            cleardevice();
                            putimage(0, 0, &screen);
                            putimage(x1, 150, &player12, SRCAND);
                            putimage(x1, 150, &player11, SRCPAINT);
                            putimage(x2, 150, &player22, SRCAND);
                            putimage(x2, 150, &player21, SRCPAINT);
                            putimage(x3, 150, &player32, SRCAND);
                            putimage(x3, 150, &player31, SRCPAINT);
                            DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                            FlushBatchDraw();
                            Sleep(10);
                        }
                    }
                }
                if (caozuo == L"delete")
                {
                    if (hnum == 1)
                    {
                        for (int x = 300; x >= -200; x -= 10)
                        {
                            cleardevice();
                            putimage(0, 0, &screen);
                            putimage(x, 150, &player12, SRCAND);
                            putimage(x, 150, &player11, SRCPAINT);
                            DrawAlphaBlueRect(0, 370, 800, 230, 200); 
                            outtextxy(10, 371, lastname.c_str());
                            FlushBatchDraw();
							Sleep(10);
                        }
                    }
                    else if (hnum == 2)
                    {
                        int where = 0, pos = players.find(player);
                        for (int i = 0; i < players.length(); i++)
                            if (players[i] == L' ')
                            {
                                where++;
                                if (i == pos)
                                    break;
                            }
                        int x1 = 200, x2 = 400;
                        if (where == 1)
                            for (; x1 >= -200; x1 -= 20, x2 -= 10)
                            {
                                cleardevice();
                                putimage(0, 0, &screen);
                                putimage(x1, 150, &player12, SRCAND);
                                putimage(x1, 150, &player11, SRCPAINT);
                                putimage(x2, 150, &player22, SRCAND);
                                putimage(x2, 150, &player21, SRCPAINT);
                                DrawAlphaBlueRect(0, 370, 800, 230, 200);
                                outtextxy(10, 371, lastname.c_str());
                                FlushBatchDraw();
                                Sleep(10);
                            }
                        if (where == 2)
                            for (; x2 <= 800; x1 += 10, x2 += 20)
                            {
                                cleardevice();
                                putimage(0, 0, &screen);
                                putimage(x1, 150, &player12, SRCAND);
                                putimage(x1, 150, &player11, SRCPAINT);
                                putimage(x2, 150, &player22, SRCAND);
                                putimage(x2, 150, &player21, SRCPAINT);
                                DrawAlphaBlueRect(0, 370, 800, 230, 200);
                                outtextxy(10, 371, lastname.c_str());
                                FlushBatchDraw();
                                Sleep(10);
                            }
                    }
                    else if (hnum == 3)
                    {
                        int where = 0, pos = players.find(player);
                        for (int i = 0; i < players.length(); i++)
                            if (players[i] == L' ')
                            {
                                where++;
                                if (i == pos)
                                    break;
                            }
                        int x1 = 100, x2 = 300, x3 = 500;
                        if (where == 1)
                            for (; x1 >= -200; x1 -= 30, x2 -= 10, x3 -= 10)
                            {
                                cleardevice();
                                putimage(0, 0, &screen);
                                putimage(x1, 150, &player12, SRCAND);
                                putimage(x1, 150, &player11, SRCPAINT);
                                putimage(x2, 150, &player22, SRCAND);
                                putimage(x2, 150, &player21, SRCPAINT);
                                putimage(x3, 150, &player32, SRCAND);
                                putimage(x3, 150, &player31, SRCPAINT);
                                DrawAlphaBlueRect(0, 370, 800, 230, 200);
                                outtextxy(10, 371, lastname.c_str());
                                FlushBatchDraw();
                                Sleep(10);
                            }
                        if (where == 2)
                            for (; x2 >= -200; x1 += 4, x2 -= 20, x3 -= 4)
                            {
                                cleardevice();
                                putimage(0, 0, &screen);
                                putimage(x1, 150, &player12, SRCAND);
                                putimage(x1, 150, &player11, SRCPAINT);
                                putimage(x2, 150, &player22, SRCAND);
                                putimage(x2, 150, &player21, SRCPAINT);
                                putimage(x3, 150, &player32, SRCAND);
                                putimage(x3, 150, &player31, SRCPAINT);
                                DrawAlphaBlueRect(0, 370, 800, 230, 200);
                                outtextxy(10, 371, lastname.c_str());
                                FlushBatchDraw();
                                Sleep(10);
                            }
                        if (where == 3)
                            for (; x3 <= 800; x1 += 10, x2 += 10, x3 += 30)
                            {
                                cleardevice();
                                putimage(0, 0, &screen);
                                putimage(x1, 150, &player12, SRCAND);
                                putimage(x1, 150, &player11, SRCPAINT);
                                putimage(x2, 150, &player22, SRCAND);
                                putimage(x2, 150, &player21, SRCPAINT);
                                putimage(x3, 150, &player32, SRCAND);
                                putimage(x3, 150, &player31, SRCPAINT);
                                DrawAlphaBlueRect(0, 370, 800, 230, 200);
                                outtextxy(10, 371, lastname.c_str());
                                FlushBatchDraw();
                                Sleep(10);
                            }
                    }
                    if (players.find(player) != wstring::npos)
                    {
                        int pos = players.find(player);
                        players.erase(pos, player.length());
                    }
                    if (player == L" lhx")
                    {
                        if (lastname.find(L"李皓轩") != wstring::npos)
                        {
                            int pos = lastname.find(L"李皓轩");
                            lastname.erase(pos, 3);
                        }
                        if (lastname.find(L"&&李皓轩") != wstring::npos)
                        {
                            int pos = lastname.find(L"&&李皓轩");
                            lastname.erase(pos, 5);
                        }
                    }
                    else if (player == L" lzy")
                    {
                        if (lastname.find(L"李卓阳") != wstring::npos)
                        {
                            int pos = lastname.find(L"李卓阳");
                            lastname.erase(pos, 3);
                        }
                        if (lastname.find(L"&&李卓阳") != wstring::npos)
                        {
                            int pos = lastname.find(L"&&李卓阳");
                            lastname.erase(pos, 5);
                        }
                    }
                    else if (player == L" zjh")
                    {
                        if (lastname.find(L"赵炯赫") != wstring::npos)
                        {
                            int pos = lastname.find(L"赵炯赫");
                            lastname.erase(pos, 3);
                        }
                        if (lastname.find(L"&&赵炯赫") != wstring::npos)
                        {
                            int pos = lastname.find(L"&&赵炯赫");
                            lastname.erase(pos, 5);
                        }
                    }
                    else if (player == L" bsj")
                    {
                        if (lastname.find(L"毕书俊") != wstring::npos)
                        {
                            int pos = lastname.find(L"毕书俊");
                            lastname.erase(pos, 3);
                        }
                        if (lastname.find(L"&&毕书俊") != wstring::npos)
                        {
                            int pos = lastname.find(L"&&毕书俊");
                            lastname.erase(pos, 5);
                        }
                    }
                    else if (player != L" bsj" && player != L" lhx" && player != L" lzy" && player != L" zjh")
                    {
                        if (lastname.find(L"NPC") != wstring::npos)
                        {
                            int pos = lastname.find(L"NPC");
                            lastname.erase(pos, 3);
                        }
                        if (lastname.find(L"&&NPC") != wstring::npos)
                        {
                            int pos = lastname.find(L"&&NPC");
                            lastname.erase(pos, 5);
                        }
                    }
                }
                if (caozuo == L"dload")
                {
                    players = L"";
                    players += player;
                    if (player == L" lhx")
                        lastname = L"李皓轩";
                    else if (player == L" lzy")
                        lastname = L"李卓阳";
                    else if (player == L" zjh")
                        lastname = L"赵炯赫";
                    else if (player == L" bsj")
                        lastname = L"毕书俊";
                    else if (player != L" bsj" && player != L" lhx" && player != L" lzy" && player != L" zjh")
                        lastname = L"NPC";
                    if (hnum == 1)
                    {
                        for (int x = 300; x >= -200; x -= 10)
                        {
                            cleardevice();
                            putimage(0, 0, &screen);
                            putimage(x, 150, &player12, SRCAND);
                            putimage(x, 150, &player11, SRCPAINT);
                            DrawAlphaBlueRect(0, 370, 800, 230, 200);
                            outtextxy(10, 371, lastname.c_str());
                            FlushBatchDraw();
                            Sleep(10);
                        }
                    }
                    else if (hnum == 2)
                    {
                        int x1 = 200,x2=400;
                        for (; x2 >= -200; x1 -= 40, x2 -= 60)
                        {
                            cleardevice();
                            putimage(0, 0, &screen);
                            putimage(x1, 150, &player12, SRCAND);
                            putimage(x1, 150, &player11, SRCPAINT);
							putimage(x2, 150, &player22, SRCAND);
							putimage(x2, 150, &player21, SRCPAINT);
                            DrawAlphaBlueRect(0, 370, 800, 230, 200);
                            outtextxy(10, 371, lastname.c_str());
                            FlushBatchDraw();
                            Sleep(10);
                        }
                    }
                    else if (hnum == 3)
                    {
                        int x1 = 100, x2 = 300,x3=500;
                        for (; x3 >= -200; x1 -= 30, x2 -= 50, x3 -= 70)
                        {
                            cleardevice();
                            putimage(0, 0, &screen);
                            putimage(x1, 150, &player12, SRCAND);
                            putimage(x1, 150, &player11, SRCPAINT);
                            putimage(x2, 150, &player22, SRCAND);
                            putimage(x2, 150, &player21, SRCPAINT);
							putimage(x3, 150, &player32, SRCAND);
							putimage(x3, 150, &player31, SRCPAINT);
                            DrawAlphaBlueRect(0, 370, 800, 230, 200);
                            outtextxy(10, 371, lastname.c_str());
                            FlushBatchDraw();
                            Sleep(10);
                        }
                    }
                    hnum = 1;
                    player11.Resize(0, 0);
                    player21.Resize(0, 0);
                    player31.Resize(0, 0);
                    player12.Resize(0, 0);
                    player22.Resize(0, 0);
                    player32.Resize(0, 0);
                    for (int i = 0; i < players.length(); i++)
                    {
                        if (players[i] == L' ')
                        {
                            wstring linshijicun1 = L"image/player/", linshijicun2;
                            for (int j = i + 1; players[j] != L' ' && j < players.length(); j++)
                                linshijicun1 += players[j];
                            linshijicun2 = linshijicun1;
                            linshijicun1 += L"1.jpg";
                            linshijicun2 += L"2.jpg";
                            loadimage(&player11, linshijicun1.c_str(), 200, 366);
                            loadimage(&player12, linshijicun2.c_str(), 200, 366);

                        }
                    }
                    for (int x = 800; x >= 300; x -= 10)
                    {
                        cleardevice();
						putimage(0, 0, &screen);
                        putimage(x, 150, &player12, SRCAND);
                        putimage(x, 150, &player11, SRCPAINT);
                        DrawAlphaBlueRect(0, 370, 800, 230, 200);
                        outtextxy(10, 371, lastname.c_str());
                        FlushBatchDraw();
                        Sleep(10);
                    }
                }


            }//烂尾
            if (thetagname == L"screen")
            {
                wstring thetagtext = findTagtext(line);
                wstring screenname, screenderss = L"image/screen/";
                for (int i = 0; i < thetagtext.length(); i++)
                    if (thetagtext[i] == ' ')
                    {
                        for (int j = 0; j < i; j++)
                            screenname += thetagtext[j];
                        for (int j = i + 1; j < thetagtext.length(); j++)
                            screenderss += thetagtext[j];
                        break;
                    }
                loadimage(&screen, screenderss.c_str(), 800, 600);
                cleardevice();
                putimage(0, 0, &screen);
                switch (hnum)
                {
                case 1:
                    putimage(300, 150, &player12, SRCAND);
                    putimage(300, 150, &player11, SRCPAINT);
                    break;
                case 2:
                    putimage(200, 150, &player12, SRCAND);
                    putimage(200, 150, &player11, SRCPAINT);
                    putimage(400, 150, &player22, SRCAND);
                    putimage(400, 150, &player21, SRCPAINT);
                    break;
                case 3:
                    putimage(100, 150, &player12, SRCAND);
                    putimage(100, 150, &player11, SRCPAINT);
                    putimage(300, 150, &player22, SRCAND);
                    putimage(300, 150, &player21, SRCPAINT);
                    putimage(500, 150, &player32, SRCAND);
                    putimage(500, 150, &player31, SRCPAINT);
                    break;

                default:
                    break;
                }
                DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                for (int x = -textwidth(screenname.c_str()); x <= 0; x += 10)
                {
                    cleardevice();
                    putimage(0, 0, &screen);
                    switch (hnum)
                    {
                    case 1:
                        putimage(300, 150, &player12, SRCAND);
                        putimage(300, 150, &player11, SRCPAINT);
                        break;
                    case 2:
                        putimage(200, 150, &player12, SRCAND);
                        putimage(200, 150, &player11, SRCPAINT);
                        putimage(400, 150, &player22, SRCAND);
                        putimage(400, 150, &player21, SRCPAINT);
                        break;
                    case 3:
                        putimage(100, 150, &player12, SRCAND);
                        putimage(100, 150, &player11, SRCPAINT);
                        putimage(300, 150, &player22, SRCAND);
                        putimage(300, 150, &player21, SRCPAINT);
                        putimage(500, 150, &player32, SRCAND);
                        putimage(500, 150, &player31, SRCPAINT);
                        break;

                    default:
                        break;
                    }
                    DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                    solidrectangle(x, 100, x + textwidth(screenname.c_str()), 117);
                    settextcolor(BLACK);
                    outtextxy(x, 101, screenname.c_str());
                    FlushBatchDraw();
                    Sleep(10);
                }
                cleardevice();
                putimage(0, 0, &screen);
                switch (hnum)
                {
                case 1:
                    putimage(300, 150, &player12, SRCAND);
                    putimage(300, 150, &player11, SRCPAINT);
                    break;
                case 2:
                    putimage(200, 150, &player12, SRCAND);
                    putimage(200, 150, &player11, SRCPAINT);
                    putimage(400, 150, &player22, SRCAND);
                    putimage(400, 150, &player21, SRCPAINT);
                    break;
                case 3:
                    putimage(100, 150, &player12, SRCAND);
                    putimage(100, 150, &player11, SRCPAINT);
                    putimage(300, 150, &player22, SRCAND);
                    putimage(300, 150, &player21, SRCPAINT);
                    putimage(500, 150, &player32, SRCAND);
                    putimage(500, 150, &player31, SRCPAINT);
                    break;

                default:
                    break;
                }
                DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                solidrectangle(0, 100, textwidth(screenname.c_str()), 117);
                settextcolor(BLACK);
                outtextxy(0, 101, screenname.c_str());
                FlushBatchDraw();
                Sleep(1000);
                for (int x = 0; x >= -textwidth(screenname.c_str()); x -= 10)
                {
                    cleardevice();
                    putimage(0, 0, &screen);
                    switch (hnum)
                    {
                    case 1:
                        putimage(300, 150, &player12, SRCAND);
                        putimage(300, 150, &player11, SRCPAINT);
                        break;
                    case 2:
                        putimage(200, 150, &player12, SRCAND);
                        putimage(200, 150, &player11, SRCPAINT);
                        putimage(400, 150, &player22, SRCAND);
                        putimage(400, 150, &player21, SRCPAINT);
                        break;
                    case 3:
                        putimage(100, 150, &player12, SRCAND);
                        putimage(100, 150, &player11, SRCPAINT);
                        putimage(300, 150, &player22, SRCAND);
                        putimage(300, 150, &player21, SRCPAINT);
                        putimage(500, 150, &player32, SRCAND);
                        putimage(500, 150, &player31, SRCPAINT);
                        break;

                    default:
                        break;
                    }
                    DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                    solidrectangle(x, 100, x + textwidth(screenname.c_str()), 117);
                    settextcolor(BLACK);
                    outtextxy(x, 101, screenname.c_str());
                    FlushBatchDraw();
                    Sleep(10);
                }
                cleardevice();
                putimage(0, 0, &screen);
                switch (hnum)
                {
                case 1:
                    putimage(300, 150, &player12, SRCAND);
                    putimage(300, 150, &player11, SRCPAINT);
                    break;
                case 2:
                    putimage(200, 150, &player12, SRCAND);
                    putimage(200, 150, &player11, SRCPAINT);
                    putimage(400, 150, &player22, SRCAND);
                    putimage(400, 150, &player21, SRCPAINT);
                    break;
                case 3:
                    putimage(100, 150, &player12, SRCAND);
                    putimage(100, 150, &player11, SRCPAINT);
                    putimage(300, 150, &player22, SRCAND);
                    putimage(300, 150, &player21, SRCPAINT);
                    putimage(500, 150, &player32, SRCAND);
                    putimage(500, 150, &player31, SRCPAINT);
                    break;

                default:
                    break;
                }
                DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                FlushBatchDraw();
            }
            if (thetagname == L"introduce")
            {
                wstring thetagtext = findTagtext(line);
                wstring player, introduce;
                for (int i = 0; i < thetagtext.length(); i++)
                    if (thetagtext[i] == ' ')
                    {
                        for (int j = 0; j < i; j++)
                            player += thetagtext[j];
                        for (int j = i + 1; j < thetagtext.length(); j++)
                            introduce += thetagtext[j];
                    }
                players += L' ';
                players += player;
                hnum = 1;
                for (int i = 0; i < players.length(); i++)
                {
                    if (players[i] == L' ')
                    {
                        wstring linshijicun1 = L"image/player/", linshijicun2, nowname;
                        for (int j = i + 1; players[j] != L' ' && j < players.length(); j++)
                        {
                            nowname += players[j];
                            linshijicun1 += players[j];
                        }
                        if (nowname == L"lhx")
                            lastname = L"李皓轩";
                        else if (nowname == L"lzy")
                            lastname = L"李卓阳";
                        else if (nowname == L"zjh")
                            lastname = L"赵炯赫";
                        else if (nowname == L"bsj")
                            lastname = L"毕书俊";
                        else if (nowname != L"bsj" && nowname != L"lhx" && nowname != L"lzy" && nowname != L"zjh")
                            lastname = L"NPC";
                        linshijicun2 = linshijicun1;
                        linshijicun1 += L"1.jpg";
                        linshijicun2 += L"2.jpg";
                        loadimage(&player11, linshijicun1.c_str(), 200, 366);
                        loadimage(&player12, linshijicun2.c_str(), 200, 366);
                        hnum++;
                    }
                }
                for (int x = 800; x >= 300; x -= 20)
                {
                    wstring linshi;
                    cleardevice();
                    putimage(0, 0, &screen);
                    putimage(x, 150, &player12, SRCAND);
                    putimage(x, 150, &player11, SRCPAINT);
                    DrawAlphaBlueRect(0, 370, 800, 230, 200); outtextxy(10, 371, lastname.c_str());
                    outtextxy(10, 371, lastname.c_str());
                    Sleep(10);
                    FlushBatchDraw();
                }
                slow(introduce);
                getawait();

            }
            if (thetagname == L"music")
            {
                mciSendString(_T("stop music"), NULL, 0, NULL);
                mciSendString(_T("close music"), NULL, 0, NULL);
				wstring musicname = L"open image/music/";
                musicname += findTagtext(line);
				musicname += L" alias music";
                mciSendString(musicname.c_str(), NULL, 0, NULL);
                mciSendString(_T("play music repeat"), NULL, 0, NULL);
            }
            if (thetagname == L"slow")
            {

            }
            //及记得写FlushBatchDraw();
            //和Sleep(30000);
        }
        else
        {
            cleardevice();
            putimage(0, 0, &screen);
            switch (hnum)
            {
            case 1:
                putimage(300, 150, &player12, SRCAND);
                putimage(300, 150, &player11, SRCPAINT);
                break;
            case 2:
                putimage(200, 150, &player12, SRCAND);
                putimage(200, 150, &player11, SRCPAINT);
                putimage(400, 150, &player22, SRCAND);
                putimage(400, 150, &player21, SRCPAINT);
                break;
            case 3:
                putimage(100, 150, &player12, SRCAND);
                putimage(100, 150, &player11, SRCPAINT);
                putimage(300, 150, &player22, SRCAND);
                putimage(300, 150, &player21, SRCPAINT);
                putimage(500, 150, &player32, SRCAND);
                putimage(500, 150, &player31, SRCPAINT);
                break;

            default:
                break;
            }
            DrawAlphaBlueRect(0, 370, 800, 230, 200);
            wstring whatfind, nowname;
            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == ' ')
                {
                    for (int j = 0; j < i; j++)
                        nowname += line[j];
                    for (int j = i + 1; j < line.length(); j++)
                        whatfind += line[j];
                }
            }
            lastname = L"";
            lastname = nowname;
            outtextxy(10, 371, lastname.c_str());
            slow(whatfind.c_str());
            getawait();
        }
    }
    file.close();
}
void help()
{
    /*initgraph(800, 600);
    //SetWorkingImage(NULL);
    //setbkcolor(WHITE);
    cleardevice();
    Sleep(3000);
    TCHAR s[] = _T("尚未开发！这里是帮助！");
    setbkmode(TRANSPARENT);
    outtextxy(300, 200, s);
    cleardevice();
    Sleep(3000);
    //closegraph();*/
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    wifstream file("help.txt");
    file.imbue(locale(file.getloc(), new codecvt_utf8<wchar_t>));
    BeginBatchDraw();
	fillrectangle(200, 100, 600, 500);
    wstring filenerong=L"",really;
	//file >> filenerong;
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    while(getline(file, filenerong))
    {
		really += filenerong;
        really += L"\n";
	}
	int x = 200, y = 100;
    for (int i = 0; i < really.length(); i++)
    {
        
        if (x+23>600)
        {
            x = 200;
            y += 15;
            i--;
        }
        else
        {
            wstring now;
            now = really[i];
            x += 13;
            outtextxy(x, y, now.c_str());
            x += textwidth(now.c_str());
        }
    }
    //outtextxy(200, 100, filenerong.c_str());
    //settextcolor(BLACK);
    //setbkmode(TRANSPARENT);
	//
    FlushBatchDraw();
    getawait();
}
void game()
{
    /*initgraph(800, 600);
    //setbkcolor(RED);
    TCHAR s[] = _T("尚未开发！这里是游戏！");
    outtextxy(0, 0, s);
    Sleep(3000);
    closegraph();*/
    IMAGE screen;
	loadimage(&screen, _T("image/screen/gd.jpg"), 800, 600);
    /*POINT point1[] = { {215,300},{ 315,300 } ,{265,500} ,{165,500} };
    POINT point2[] = { {325,300},{ 375,100 } ,{475,100} ,{425,300} };
    POINT point3[] = { {635,300},{ 735,300 } ,{685,500} ,{585,500} };
    POINT point1[] = { {215,300},{ 315,300 } ,{265,500} ,{165,500} };
    POINT point2[] = { {325,300},{ 375,100 } ,{475,100} ,{425,300} };
    POINT point3[] = { {635,300},{ 735,300 } ,{685,500} ,{585,500} };*/
    POINT point1[] = { {100,500},{250,500  } ,{300,300} ,{150,300} };
    POINT point2[] = { {349,300},{499,300  } ,{549,100} ,{399,100} };
    POINT point3[] = { {550,300},{700,300  } ,{650,500} ,{500,500} };
    setbkcolor(RGB(71,89,96));
    int where = 0;
    ExMessage msg{ 0 };
    while(1)
    {
        BeginBatchDraw();
        cleardevice();
        putimage(0, 0, &screen);
        if (where == 1)
        {
            setfillcolor(YELLOW);
            fillpolygon(point1, 4);
        }
        else
        {
            setfillcolor(WHITE);
            fillpolygon(point1, 4);
        }
        if (where == 2)
        {
            setfillcolor(YELLOW);
            fillpolygon(point2, 4);
        }
        else
        {
            setfillcolor(WHITE);
            fillpolygon(point2, 4);
        }
        if (where == 3)
        {
            setfillcolor(YELLOW);
            fillpolygon(point3, 4);
        }
        else
        {
            setfillcolor(WHITE);
            fillpolygon(point3, 4);
        }
        FlushBatchDraw();
        while(peekmessage(&msg))
        {
            if (msg.message == WM_MOUSEMOVE)
            {
                POINT point = {msg.x,msg.y};
                if (isPointInParallelogram(point1,point))
                    where = 1;
                else if (isPointInParallelogram(point2, point))
                    where = 2;
                else if (isPointInParallelogram(point3, point))
                    where = 3;
                else
                    where = 0;
            }
            if (msg.message == WM_LBUTTONDOWN)
            {
                POINT point = { msg.x,msg.y };
                if (isPointInParallelogram(point1, point))
                {
                    cleardevice();
                    int howManyFiles = 0;
                    int allReadyFile = 0;
                    IMAGE screen1;
                    POINT right[] = { {270,600},{800,600},{800,0},{500,0} };
                    string filenerong;

                        fstream file{ "image/001/date.txt" };
                        file >> filenerong;
						allReadyFile = stoi(filenerong);
						file.close();
                        for(int i=1;1;i++)
                        {
							string filename = "image/001/" + to_string(i) + ".txt";
                            file.open(filename);
                            if (!file)
								break;
                            else
                            {
                                howManyFiles++;
                                file.close();
							}
                        }
					loadimage(&screen1, _T("image/screen/classroom2.jpg"), 800, 600);
                    while (1)
                    {
						putimage(0, 0, &screen1);
                        setfillcolor(RGB(9,52,100));
                        solidpolygon(right, 4);
                        FlushBatchDraw();
                    }
                }
                else if (isPointInParallelogram(point2, point))
                {

                }
                else if (isPointInParallelogram(point3, point))
                {

                }
                else
                    ;
            }
		}
    }
}
int main()
{
    //mciSendString(_T("open image/music/0001.mp3 Alias movie"), NULL, 0, NULL);
    //juqing("image/0001/0001.txt");
    IMAGE p1, p2,p22, screen0, screen1, screen2, screen3;
    IMAGE button111, button112, button121, button122, button131, button132;
    IMAGE button211, button212, button221, button222;
    IMAGE button311, button312, button321, button322;
    IMAGE button411, button412, button421, button422;
    loadimage(&p1, _T("image/frist taitel.png"));//
    loadimage(&p2, _T("image/qbz.JPG"),300,250);
    loadimage(&p22, _T("image/qbz2.png"), 300, 250);
    loadimage(&button111, _T("image/button/button1 1 1.png"));
    loadimage(&button112, _T("image/button/button1 1 2.png"));
    loadimage(&button121, _T("image/button/button1 2 1.png"));
    loadimage(&button122, _T("image/button/button1 2 2.png"));
    loadimage(&button131, _T("image/button/button1 3 1.png"));
    loadimage(&button132, _T("image/button/button1 3 2.png"));

    loadimage(&button211, _T("image/button/button2 1 1.png"));
    loadimage(&button212, _T("image/button/button2 1 2.png"));
    loadimage(&button221, _T("image/button/button2 2 1.png"));
    loadimage(&button222, _T("image/button/button2 2 2.png"));

    loadimage(&button311, _T("image/button/button3 1 1.png"));
    loadimage(&button312, _T("image/button/button3 1 2.png"));
    loadimage(&button321, _T("image/button/button3 2 1.png"));
    loadimage(&button322, _T("image/button/button3 2 2.png"));

    loadimage(&button411, _T("image/button/button4 1 1.png"));
    loadimage(&button412, _T("image/button/button4 1 2.png"));
    loadimage(&button421, _T("image/button/button4 2 1.png"));
    loadimage(&button422, _T("image/button/button4 2 2.png"));
    
    loadimage(&screen0, _T("image/screen/screen0.jpg"), 800, 600);
    loadimage(&screen1, _T("image/screen/screen1.jpg"), 800, 600);
    loadimage(&screen2, _T("image/screen/screen2.jpg"), 800, 600);
    loadimage(&screen3, _T("image/screen/screen3.jpg"), 800, 600);
    initgraph(800, 600);
    //setbkcolor(WHITE);
    /*//
    string str="我草泥马";
    wstring str1 = stringToWstring(str);
    outtextxy(0, 0, str1.c_str());
    */
    putimage(0, 0, &p1);
    //Sleep(3000);
    ///
    BOOL filehave;
    fstream file;
    file.open("image/date/self.txt");
    if (!file)
        filehave = 0;
    else
    {
        string filenerong;
        file >> filenerong;
        if (filenerong.empty())
            filehave = 0;
        else
			filehave = 1;
    }
    file.close();
    ExMessage msg{ 0 };
    int b = 1;
    mciSendString(_T("open image/music/0001.mp3 Alias movie"), NULL, 0, NULL);
    mciSendString(_T("play movie repeat"), NULL, 0, NULL);
    while (1)
    {
        BeginBatchDraw();
        cleardevice();
        /*initgraph(800, 600);*/

        
        switch (b)
        {
        case 0:
            putimage(0, 0, &screen0);
            /*setfillcolor(BLACK);
            solidrectangle(0,0,300,600);*/
            putimage(0, 0, &p22, SRCAND);
            putimage(0, 0, &p2, SRCPAINT);
            putimage(0, 250, &button122, SRCAND);
            putimage(0, 250, &button121, SRCPAINT);
            putimage(0, 300, &button212, SRCAND);
            putimage(0, 300, &button211, SRCPAINT);
            putimage(0, 350, &button312, SRCAND);
            putimage(0, 350, &button311, SRCPAINT);
            putimage(0, 400, &button412, SRCAND);
            putimage(0, 400, &button411, SRCPAINT);
            FlushBatchDraw();
            break;
        case 1:
            putimage(0, 0, &screen1);
            /*setfillcolor(BLACK);
            solidrectangle(0,0,300,600);*/
            putimage(0, 0, &p22, SRCAND);
            putimage(0, 0, &p2, SRCPAINT);
            if (filehave)
            {
                putimage(0, 250, &button112, SRCAND);
                putimage(0, 250, &button111, SRCPAINT);
            }
            else
            {
                putimage(0, 250, &button132, SRCAND);
                putimage(0, 250, &button131, SRCPAINT);
            }
            putimage(0, 300, &button222, SRCAND);
            putimage(0, 300, &button221, SRCPAINT);
            putimage(0, 350, &button312, SRCAND);
            putimage(0, 350, &button311, SRCPAINT);
            putimage(0, 400, &button412, SRCAND);
            putimage(0, 400, &button411, SRCPAINT);
            FlushBatchDraw();
            break;
        case 2:
            putimage(0, 0, &screen2);
            /*setfillcolor(BLACK);
            solidrectangle(0,0,300,600);*/
            putimage(0, 0, &p22, SRCAND);
            putimage(0, 0, &p2, SRCPAINT);
            if (filehave)
            {
                putimage(0, 250, &button112, SRCAND);
                putimage(0, 250, &button111, SRCPAINT);
            }
            else
            {
                putimage(0, 250, &button132, SRCAND);
                putimage(0, 250, &button131, SRCPAINT);
            }
            putimage(0, 300, &button212, SRCAND);
            putimage(0, 300, &button211, SRCPAINT);
            putimage(0, 350, &button322, SRCAND);
            putimage(0, 350, &button321, SRCPAINT);
            putimage(0, 400, &button412, SRCAND);
            putimage(0, 400, &button411, SRCPAINT);
            FlushBatchDraw();
            break;
        case 3:
            putimage(0, 0, &screen3);
            /*setfillcolor(BLACK);
            solidrectangle(0,0,300,600);*/
            putimage(0, 0, &p22, SRCAND);
            putimage(0, 0, &p2, SRCPAINT);
            if (filehave)
            {
                putimage(0, 250, &button112, SRCAND);
                putimage(0, 250, &button111, SRCPAINT);
            }
            else
            {
                putimage(0, 250, &button132, SRCAND);
                putimage(0, 250, &button131, SRCPAINT);
            }
            putimage(0, 300, &button212, SRCAND);
            putimage(0, 300, &button211, SRCPAINT);
            putimage(0, 350, &button312, SRCAND);
            putimage(0, 350, &button311, SRCPAINT);
            putimage(0, 400, &button422, SRCAND);
            putimage(0, 400, &button421, SRCPAINT);
            FlushBatchDraw();
            break;
        default:
            outtextxy(0, 0, char("一些不好的事情发生了"));
            break;
        }
        while (peekmessage(&msg))//获得消息
        {
            if (msg.message == WM_KEYDOWN)//判断消息是否是由键盘发出
            {
                switch (msg.vkcode)//如果是方向键
                {
                case VK_UP://上
                    if (filehave)
                        if (b - 1 >= 0)
                            b--;
                    if (!filehave)
                        if (b - 1 >= 1)
                            b--;
                    break;
                case VK_DOWN://下
                    if (b + 1 <= 3)
                        b++;
                    break;
                case 'W':
                    if (filehave)
                        if (b - 1 >= 0)
                            b--;
                    if (!filehave)
                        if (b - 1 >= 1)
                            b--;
                    break;
                case 'S':
                    if (b + 1 <= 3)
                        b++;
                    break;
                case VK_RETURN:
                    switch (b)
                    {
                    case 0:
                        mciSendString(_T("stop movie"), NULL, 0, NULL);
                        cleardevice();
                        game();
                        break;
                    case 1:
                        mciSendString(_T("stop movie"), NULL, 0, NULL);
                        closegraph();
                        juqing("image/start/0001.txt");
                        file.open("image/date/self.txt", ios::in);
                        if (file) 
                        {
                            // 文件存在，清空内容
                            file.close();
                            file.open("image/date/self.txt", ios::out | ios::trunc);
                            file << "20 20 20 20 20 20 20 20 20 20 20 自己 ";
                            file.close();
                        }
                        else 
                        {
                            file.open("image/date/self.txt", ios::out);
                            file << "20 20 20 20 20 20 20 20 20 20 20 自己 ";
                            file.close();
                        }
						filehave = 1;
                        break;
                    case 2:
                        mciSendString(_T("stop movie"), NULL, 0, NULL);
                        return 0;
                        break;
                    case 3:
                        mciSendString(_T("stop movie"), NULL, 0, NULL);
                        help();
                        break;
                    default:
                    {
                        mciSendString(_T("play movie repeat"), NULL, 0, NULL);
                        cleardevice();
                        outtextxy(0, 0, char("一些不好的事情发生了"));
                        return 0;
                        break;
                    }
                    }
                    break;

                    /*case VK_LEFT://左
                        //具体行动
                    case VK_RIGHT://右
                        //具体行动
                    case 'A':

                    case 'D':*/
                }


            }
            if (msg.message == WM_MOUSEMOVE)
            {
                if (msg.x >= 0 && msg.x <= 300 && msg.y >= 250 && msg.y <= 300 && filehave)
                    b = 0;
                if (msg.x >= 0 && msg.x <= 300 && msg.y >= 300 && msg.y <= 350)
                    b = 1;
                if (msg.x >= 0 && msg.x <= 300 && msg.y >= 350 && msg.y <= 400)
                    b = 2;
                if (msg.x >= 0 && msg.x <= 300 && msg.y >= 400 && msg.y <= 450)
                    b = 3;
            }
            if (msg.message == WM_LBUTTONDOWN)
                switch (b)
                {
                case 0:
                    if(msg.x >= 0 && msg.x <= 300 && msg.y >= 250 && msg.y <= 300 && filehave)
                    {
                        mciSendString(_T("stop movie"), NULL, 0, NULL);
                        cleardevice();
                        game();
                        break;
                    }
                    break;
                case 1:
                    if(msg.x >= 0 && msg.x <= 300 && msg.y >= 300 && msg.y <= 350)
                    {
                        mciSendString(_T("stop movie"), NULL, 0, NULL);
                        closegraph();
                        juqing("image/start/0001.txt");
                        file.open("image/date/self.txt", ios::in);
                        if (file)
                        {
                            // 文件存在，清空内容
                            file.close();
                            file.open("image/date/self.txt", ios::out | ios::trunc);
                            file << "20 20 20 20 20 20 20 20 20 20 20 自己 ";
                            file.close();
                        }
                        else
                        {
                            file.open("image/date/self.txt", ios::out);
                            file << "20 20 20 20 20 20 20 20 20 20 20 自己 ";
                            file.close();
                        }
                        filehave = 1;
                        break;
                    }
                    break;
                case 2:
                    if(msg.x >= 0 && msg.x <= 300 && msg.y >= 350 && msg.y <= 400)
                    {
                        mciSendString(_T("stop movie"), NULL, 0, NULL);
                        return 0;
                        break;
                    }
                    break;
                case 3:
                    if(msg.x >= 0 && msg.x <= 300 && msg.y >= 400 && msg.y <= 450)
                    {
                        mciSendString(_T("stop movie"), NULL, 0, NULL);
                        help();
                        break;
                    }
                    break;
                default:
                {
                    mciSendString(_T("play movie repeat"), NULL, 0, NULL);
                    cleardevice();
                    outtextxy(0, 0, char("一些不好的事情发生了"));
                    return 0;
                    break;
                }
                }
            
            //a = 0;
        }
    }
}