/* designer notes
   i shall perservere untill i either have 500 messages total or i have 100 messages from start to end*/

#include "Resource.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

string ok_str = "ok";
string yes_str = "yes";
string no_str = "no";
string retry_str = "retry";
string cancel_str = "cancel";
string last_str = "last";

class msghandlerbase // class to handle messages obviously
{
    /*notes: functions passed to setcall must be void functions with no parameters*/
public:
    //variables

    wstring infotext; //the text in the message
    wstring captionstring; //the caption at the top of the message
    wstring altstringforok;
    bool okstrbool;
    wstring altstringforyes;
    bool yesstrbool;
    wstring altstringforno;
    bool nostrbool;
    struct lastmsgbasereturnedInfoStruct
    {
        msghandlerbase * last; //last msgbaseobject from this msgbaseobject
        unsigned int buttonpressed; //id of button pressed
    }InfoStructLastMessage;
    static msghandlerbase * lastmsg; // used to return to the immediately last message
    static int msgc; // counts message uses

    //the flags that decide things like the buttons displayed. ex: ok button the flag is MB_OK
    unsigned int flags; 

    //methods
    void setstringforcall(wstring str, string target)
        {
            if(target==yes_str)
            {
                altstringforyes = str;
                yesstrbool = true;
            }
            if(target==no_str)
            {
                altstringforno = str;
                nostrbool = true;
            }
            if(target==ok_str)
            {
                altstringforok = str;
                okstrbool = true;
            }
        }
    //sets the function to call using "string s" to decide which function to set
    void setcall(string s, msghandlerbase * mhb)
        {
            if(s == ok_str)
            {
                mhbcallon_ok = mhb;
                setcallableflagarray[0] = true;
            }

            if(s == yes_str)
            {
                mhbcallon_yes = mhb;
                setcallableflagarray[1] = true;
            }
            if(s == no_str)
            {
                mhbcallon_no = mhb;
                setcallableflagarray[2] = true;
            }
            if(s == cancel_str)
            {
                mhbcallon_cancel = mhb;
                setcallableflagarray[3] = true;
            }
            if(s == last_str)
            {
                setcallableflagarray[4] = true;
            }
            if(s == retry_str)
            {
                mhbcallon_retry = mhb;
                setcallableflagarray[5] = true;
            }
        }

    //initialise the bool array thats used to make sure we don't call an uninitialised function pointer
    msghandlerbase()
        {
            lastmsg = this; //last msg wont be null, just cause ok.
            setcallableflagarray[0] = false;
            setcallableflagarray[1] = false;
            setcallableflagarray[2] = false;
            setcallableflagarray[3] = false;
            setcallableflagarray[4] = false;
            setcallableflagarray[5] = false;
            okstrbool = false;
            nostrbool = false;
            yesstrbool = false;
        }

    //provides message handling objects that respond to buttons being pressed if available
    msghandlerbase * perform_message()
        {
            //do what we came here to do
            int i = MessageBoxW(NULL, infotext.c_str(), captionstring.c_str(), flags); 
            msgc++;
            msghandlerbase * tmp = NULL;
            //return the object next to be called
            switch(i)
            {
            case IDOK:
                if(setcallableflagarray[0])
                {
                    tmp = mhbcallon_ok;
                    InfoStructLastMessage.last = mhbcallon_ok;
                    InfoStructLastMessage.buttonpressed = IDOK;
                }
                break;
            case IDYES:
                if(setcallableflagarray[1])
                {
                    tmp = mhbcallon_yes;
                    InfoStructLastMessage.last = mhbcallon_yes;
                    InfoStructLastMessage.buttonpressed = IDYES;
                }
                break;
            case IDNO:
                if(setcallableflagarray[2])
                {
                    tmp = mhbcallon_no;
                    InfoStructLastMessage.last = mhbcallon_no;
                    InfoStructLastMessage.buttonpressed = IDNO;
                }
                break;
            case IDCANCEL:
                if(setcallableflagarray[3])
                {
                    tmp = mhbcallon_cancel;
                    InfoStructLastMessage.last = mhbcallon_cancel;
                    InfoStructLastMessage.buttonpressed = IDCANCEL;
                }
                break;
            case IDRETRY:
                if(setcallableflagarray[5])
                {
                    tmp = mhbcallon_retry;
                    InfoStructLastMessage.last = mhbcallon_retry;
                    InfoStructLastMessage.buttonpressed = IDRETRY;
                }
                break;
            }
            //if this message handling object was called with last_str then it will provide the last message handling object to be used
            if(setcallableflagarray[4])tmp = lastmsg; 
            //otherwise this object becomes the last object to be used before providing the next object
            lastmsg = this;
            if(tmp != NULL)return tmp;
            return NULL;
        }
    //provides message handling objects that respond to buttons being pressed if available for dialogs
    msghandlerbase * handle_message(unsigned int ubutton)
        {
            //set variables
            msgc++;
            msghandlerbase * tmp = NULL;
            //return the object next to be called
            switch(ubutton)
            {
            case IDOK:
                if(setcallableflagarray[0])
                {
                    tmp = mhbcallon_ok;
                    InfoStructLastMessage.last = mhbcallon_ok;
                    InfoStructLastMessage.buttonpressed = IDOK;
                }
                break;
            case IDYES:
                if(setcallableflagarray[1])
                {
                    tmp = mhbcallon_yes;
                    InfoStructLastMessage.last = mhbcallon_yes;
                    InfoStructLastMessage.buttonpressed = IDYES;
                }
                break;
            case IDNO:
                if(setcallableflagarray[2])
                {
                    tmp = mhbcallon_no;
                    InfoStructLastMessage.last = mhbcallon_no;
                    InfoStructLastMessage.buttonpressed = IDNO;
                }
                break;
            case IDCANCEL:
                if(setcallableflagarray[3])
                {
                    tmp = mhbcallon_cancel;
                    InfoStructLastMessage.last = mhbcallon_cancel;
                    InfoStructLastMessage.buttonpressed = IDCANCEL;
                }
                break;
            }
            //if this message handling object was called with last_str then it will provide the last message handling object to be used
            if(setcallableflagarray[4])tmp = lastmsg; 
            //otherwise this object becomes the last object to be used before providing the next object
            lastmsg = this;
            if(tmp != NULL)return tmp;
            return NULL;
        }
private:
    bool setcallableflagarray[6];
    msghandlerbase * mhbcallon_yes;
    msghandlerbase * mhbcallon_no;
    msghandlerbase * mhbcallon_cancel;
    msghandlerbase * mhbcallon_ok;
    msghandlerbase * mhbcallon_retry;
};

int msghandlerbase::msgc = 0;
msghandlerbase * msghandlerbase::lastmsg = NULL; //can't remember why this is here
BOOL CALLBACK gamedialogproc (HWND hDlg, unsigned int message, WPARAM wParam, LPARAM lParam);
void setdialog(HWND hDlg, msghandlerbase * msghb);
BOOL CALLBACK dproc (HWND hDlg, unsigned int message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD (wParam))
        {
        case IDOK:
            MessageBoxW(NULL, L"Hope You Like Your Death", L"Welcome To Hell", MB_OK); 
        case IDCANCEL:
            EndDialog (hDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;

}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
    DialogBox(hInstance, "STORYDIALOG", NULL, (DLGPROC)dproc);
    //message handling objects created here

    //starting and standard message objects
    msghandlerbase start = msghandlerbase();
    msghandlerbase end = msghandlerbase();
    msghandlerbase evilmsg = msghandlerbase();
    msghandlerbase wandering = msghandlerbase();
    msghandlerbase forest = msghandlerbase();
    msghandlerbase searchtown = msghandlerbase();
    msghandlerbase intown = msghandlerbase();
    msghandlerbase Barge = msghandlerbase();
    msghandlerbase nomsg = msghandlerbase();
    msghandlerbase cancelmsg = msghandlerbase();
    // library branching message objects
    msghandlerbase explorelib = msghandlerbase();
    msghandlerbase ex1 = msghandlerbase();
    msghandlerbase ex2 = msghandlerbase();
    msghandlerbase ex3 = msghandlerbase();
    msghandlerbase ex1b = msghandlerbase();
    msghandlerbase ex2b = msghandlerbase();
    msghandlerbase ex3b = msghandlerbase();
    //branches
    msghandlerbase alc1 = msghandlerbase();
    msghandlerbase bk1 = msghandlerbase();
    msghandlerbase net1 = msghandlerbase();
    msghandlerbase alc2 = msghandlerbase();
    msghandlerbase net2 = msghandlerbase();
    msghandlerbase alc3 = msghandlerbase();
    msghandlerbase alc4 = msghandlerbase();
    msghandlerbase alc5 = msghandlerbase();
    msghandlerbase net3 = msghandlerbase();
    // book loop to choose book
    msghandlerbase bkl1 = msghandlerbase();
    msghandlerbase bkl2 = msghandlerbase();
    msghandlerbase bkl3 = msghandlerbase();
    //branch for book loop
    msghandlerbase bkb1 = msghandlerbase();
    msghandlerbase bkb2 = msghandlerbase();
    msghandlerbase bkb3 = msghandlerbase();
    //books' branches
    msghandlerbase zmb1 = msghandlerbase();
    msghandlerbase aid1 = msghandlerbase();
    msghandlerbase inv1 = msghandlerbase();
    msghandlerbase zmb2 = msghandlerbase();
    msghandlerbase aid2 = msghandlerbase();
    msghandlerbase inv2 = msghandlerbase();
    msghandlerbase readingend = msghandlerbase();
    //out of the library
    msghandlerbase out = msghandlerbase();
    msghandlerbase gameupgrade1 = msghandlerbase();

    //then initialised
    start.infotext = L"Are You Evil?";
    start.captionstring = L"Quest Point 1";
    start.flags = MB_ICONEXCLAMATION | MB_YESNOCANCEL;
    start.setcall(yes_str, &evilmsg);
    start.setcall(no_str, &nomsg);
    start.setcall(cancel_str, &cancelmsg);

    evilmsg.infotext = L"Well You Shall Start In A Forest As Punishment.";
    evilmsg.captionstring = L"You Should Have Answered No";
    evilmsg.flags = MB_ICONINFORMATION | MB_OK;
    evilmsg.setcall(ok_str, &wandering);

    wandering.infotext = L"You Wander Around For Months Before You Get Out Your Phone And Use Google Maps To Go To The Nearest Town";
    wandering.captionstring = L"The Walking Would Have Charged It Thanks To Your Parachute Pants";
    wandering.flags = MB_ICONINFORMATION | MB_OK;
    wandering.setcall(ok_str, &forest);

    forest.infotext = L"You Find The Town Just Outside The Forest Do You Go In?";
    forest.captionstring = L"Invade?";
    forest.flags = MB_ICONINFORMATION | MB_YESNO;
    forest.setcall(yes_str, &searchtown);
    forest.setcall(no_str, &searchtown);

    searchtown.infotext = L"You Go Into Town, You See No One, After Running Around Looking For Someone To Fight You Get Bored And Decide To Read A Book Instead";
    searchtown.captionstring = L"I'm With → NEEEEEEEEEEERRRRRRRRRRD!!!!!!!";
    searchtown.flags = MB_ICONINFORMATION | MB_OK;
    searchtown.setcall(ok_str, &intown);

    intown.infotext = L"Your Desire To Read A Book Grows, Until Your Running Around Yelling \"CHARLES DICKENS\", Then You See A Library, You Start To Go Up To The Door";
    intown.captionstring = L"Knock First";
    intown.flags = MB_ICONINFORMATION | MB_OK;
    intown.setcall(ok_str, &Barge);

    Barge.infotext = L"You Barge Right In And Yell At The Top Of Your Lungs \"WHO THE FUCK WOULD GO TO THE LIBRARY\", To An Empty Room";
    Barge.captionstring = L"SHHHHHH!!!";
    Barge.flags = MB_ICONINFORMATION | MB_OK;
    Barge.setcall(ok_str, &explorelib);

    explorelib.infotext = L"Would You Like To Explore The Library?";
    explorelib.captionstring = L"Quest Point 2";
    explorelib.flags = MB_ICONEXCLAMATION | MB_YESNOCANCEL;
    explorelib.setcall(yes_str, &ex1);
    explorelib.setcall(no_str, &nomsg);
    explorelib.setcall(cancel_str, &cancelmsg);

    //the explore loop for the library
    ex1.infotext = L"☻You Find Some Alcohol☻";
    ex1.captionstring = L"Behind The Front Desk";
    ex1.flags = MB_ICONINFORMATION | MB_RETRYCANCEL;
    ex1.setcall(retry_str, &ex2);
    ex1.setcall(cancel_str, &ex1b);
    ex2.infotext = L"♪You Find Some Books That Explain The Current Crises♪";
    ex2.captionstring = L"On A Shelf Marked Fiction";
    ex2.flags = MB_ICONINFORMATION | MB_RETRYCANCEL;
    ex2.setcall(retry_str, &ex3);
    ex2.setcall(cancel_str, &ex2b);
    ex3.infotext = L"♥You Find A Computer With Working Internet♥";
    ex3.captionstring = L"In A Building Across The Street Called ByteBack... ...Its An Internet Cafe";
    ex3.flags = MB_ICONINFORMATION | MB_RETRYCANCEL;
    ex3.setcall(retry_str, &ex1);
    ex3.setcall(cancel_str, &ex3b);

    //branch from explore loop
    ex1b.infotext = L"Would You Like To Drink It?";
    ex1b.captionstring = L"Also 'Behind The Front Desk'";
    ex1b.flags = MB_ICONINFORMATION | MB_OKCANCEL;
    ex1b.setcall(ok_str, &alc1);
    ex1b.setcall(cancel_str, &ex2);
    ex2b.infotext = L"Would You Like To Read Them?";
    ex2b.captionstring = L"In A Nice Comfy Chair";
    ex2b.flags = MB_ICONINFORMATION | MB_OKCANCEL;
    ex2b.setcall(ok_str, &bk1);
    ex2b.setcall(cancel_str, &ex3);
    ex3b.infotext = L"Would You Like To Use The Internet To Find Out Whats Happening?";
    ex3b.captionstring = L"This Building Is Empty. It Sure Is Lonely Here";
    ex3b.flags = MB_ICONINFORMATION | MB_OKCANCEL;
    ex3b.setcall(ok_str, &net1);
    ex3b.setcall(cancel_str, &ex1);

    //branched messages
    alc1.infotext = L"You Drink Straight From The Bottle And Are Drunk In Seconds.";
    alc1.captionstring = L"Its Not OK";
    alc1.flags = MB_ICONINFORMATION | MB_OK;
    alc1.setcall(ok_str, &alc2);
    bk1.infotext = L"There Are Three Books To Read From Choose One.";
    bk1.captionstring = L"Its Not OK To Read";
    bk1.flags = MB_ICONINFORMATION | MB_OK;
    bk1.setcall(ok_str, &bkl1);
    net1.infotext = L"You Try Googling About Why There Are No People Around But...";
    net1.captionstring = L"Its Not OK To Google Your Friends Boobs";
    net1.flags = MB_ICONINFORMATION | MB_OK;
    net1.setcall(ok_str, &net2);

    net2.infotext = L"...Google Just Gives You A Results Page Filled With Memes, So Instead You...";
    net2.captionstring = L"I Have A LolCat Of My Friends Boobs";
    net2.flags = MB_ICONINFORMATION | MB_OK;
    net2.setcall(ok_str, &net3);
    alc2.infotext = L"Blindly Bumping Into Things Several Books Fall On Your Head Including SuperAids For Dummies, Your Favourite Bedtime Story";
    alc2.captionstring = L"Ahhhhh  Memories...      Who Needs Them.";
    alc2.flags = MB_ICONINFORMATION | MB_OK;
    alc2.setcall(ok_str, &alc3);
    //book loop
    bkl1.infotext = L"This Ones \"When Zombies Attack\".";
    bkl1.captionstring = L"Its About Zombies";
    bkl1.flags = MB_ICONINFORMATION | MB_RETRYCANCEL;
    bkl1.setcall(retry_str, &bkl2);
    bkl1.setcall(cancel_str, &bkb1);
    bkl2.infotext = L"This Ones \"Aliens And Their Probes:\n How My Butt Hurts\".";
    bkl2.captionstring = L"Its About Losing Your Butt Virginity";
    bkl2.flags = MB_ICONINFORMATION | MB_RETRYCANCEL;
    bkl2.setcall(retry_str, &bkl3);
    bkl2.setcall(cancel_str, &bkb2);
    bkl3.infotext = L"This Ones \"SuperAids For Dummies\".";
    bkl3.captionstring = L"Its About Cleansing The Earth Of Retards";
    bkl3.flags = MB_ICONINFORMATION | MB_RETRYCANCEL;
    bkl3.setcall(retry_str, &bkl1);
    bkl3.setcall(cancel_str, &bkb3);
    //library choices' branches...    ...HINT:better grammer equals better code and comments
    net3.infotext = L"... Watch Porn For Three Weeks...";
    net3.captionstring = L"It Says \"Got Milk?\"";
    net3.flags = MB_ICONINFORMATION | MB_OK;
    net3.setcall(ok_str, &out);
    alc3.infotext = L"Passing Out On The Book, Your Eyes Glued To The Pages, You Absorb The Contents";
    alc3.captionstring = L"Osmosis Sucks Big Time";
    alc3.flags = MB_ICONINFORMATION | MB_OK;
    alc3.setcall(ok_str, &alc4);
    alc4.infotext = L"Slowly Waking Up With A Terrible Hangover, You Find A Dildo In Your Mouth, Several Pictures Of Yourself Passed Out Naked With The Word Loser On Your Forhead And Feeling A Breaze On Your Head You Reach Up To Find Halve Your Hair Has Been Shaved";
    alc4.captionstring = L"Wait, Who Did This, There Isn't Anyone In Town";
    alc4.flags = MB_ICONINFORMATION | MB_OK;
    alc4.setcall(ok_str, &alc5);
    alc5.infotext = L"But Then You Find Your Name And Address On The Dildo And The Shaver In Your Back Pocket, Obviously You Did This To Yourself";
    alc5.captionstring = L"And I'm A Student Of Photography So Thats That Mystery Solved";
    alc5.flags = MB_ICONINFORMATION | MB_OK;
    alc5.setcall(ok_str, &out);

    //branches from book loop
    bkb1.infotext = L"You Learn About The Zombie Apocolypse That Happened Two Years Ago And Think To Yourself That It Is Strange You Never Heard About It";
    bkb1.captionstring = L"Must Have Slept Through It";
    bkb1.flags = MB_ICONINFORMATION | MB_OK;
    bkb1.setcall(ok_str, &zmb1);
    bkb2.infotext = L"You Learn About The Authors Experiences When An Alien Invasion Happened In Two Years, Wait What?...";
    bkb2.captionstring = L"Does This Make Sense?";
    bkb2.flags = MB_ICONINFORMATION | MB_OK;
    bkb2.setcall(ok_str, &inv1);
    bkb3.infotext = L"You Learn About How Republicans Gave Up Peace Talks With The Democrats And Created A Super Virus That Would Kill Any One Who Was Retarded";
    bkb3.captionstring = L"Genocide Is OK In Small Doses";
    bkb3.flags = MB_ICONINFORMATION | MB_OK;
    bkb3.setcall(ok_str, &aid1);

    zmb1.infotext = L"Zombies Are Usually Italian And Italians Smell Like Rotting Flesh So Everyone Was Driven Away By The Smell";
    zmb1.captionstring = L"Italians Are An Unwashed People";
    zmb1.flags = MB_ICONINFORMATION | MB_OK;
    zmb1.setcall(ok_str, &zmb2);
    inv1.infotext = L"...Oh Wait A Minute Its Based Two Years In The Future So The Author Is Just Psychic";
    inv1.captionstring = L"Oh OK...     ...Makes Sense...";
    inv1.flags = MB_ICONINFORMATION | MB_OK;
    inv1.setcall(ok_str, &inv2);
    aid1.infotext = L"They Assumed That All Democrats Were Idiots, But In The End All The Republicans Died Of The Virus Called SuperAids";
    aid1.captionstring = L"Paybacks A Bitch";
    aid1.flags = MB_ICONINFORMATION | MB_OK;
    aid1.setcall(ok_str, &aid2);

    zmb2.infotext = L"So That Explains The Missing People";
    zmb2.captionstring = L"And Why Theres Pizza On The Roof";
    zmb2.flags = MB_ICONINFORMATION | MB_OK;
    zmb2.setcall(ok_str, &readingend);
    inv2.infotext = L"Everyone Was Abducted And Taken To The Moon To Eat Cheese For The Rest Of Their Lives";
    inv2.captionstring = L"Now You've Lost Me";
    inv2.flags = MB_ICONINFORMATION | MB_OK;
    inv2.setcall(ok_str, &readingend);
    aid2.infotext = L"And Because All Democrats Are Secretly Republican At Heart The World Was Left Empty";
    aid2.captionstring = L"I'm Not Republican Or Democratic I'm Spanish";
    aid2.flags = MB_ICONINFORMATION | MB_OK;
    aid2.setcall(ok_str, &readingend);

    readingend.infotext = L"After The Seven Months It Took To Read The Book, Your Too Tired To Read The Others";
    readingend.captionstring = L"Time Flies When Your Wasting Time";
    readingend.flags = MB_ICONINFORMATION | MB_OK;
    readingend.setcall(ok_str, &out);

    out.infotext = L"Although Your Adventures In The Library Were Awesome Its Probably Time To Leave, Should We Continue The Story Outside?";
    out.captionstring = L"Sex Drugs And Rock 'N' Roll";
    out.flags = MB_ICONINFORMATION | MB_YESNOCANCEL;
    out.setcall(yes_str, &gameupgrade1);
    out.setcall(no_str, &nomsg);
    out.setcall(cancel_str, &cancelmsg);

    gameupgrade1.infotext = L"I Think We Should Change The Game. I'm Sick Of All These Yes No Cancel Messages. Aren't You Tired of Just Answering OK All The Time?";
    gameupgrade1.captionstring = L"Before We Leave";
    gameupgrade1.flags = MB_ICONINFORMATION | MB_YESNOCANCEL;
    //gameupgrade1.setcall(yes_str, &gameupgrade1);
    gameupgrade1.setcall(no_str, &nomsg);
    gameupgrade1.setcall(cancel_str, &cancelmsg);

    nomsg.infotext = L"I Dare You To Say No Again Mother F^%$#&!";
    nomsg.captionstring = L"\"No\" Is A Swear Word";
    nomsg.flags = MB_ICONINFORMATION | MB_OK;
    nomsg.setcall(last_str, nomsg.lastmsg);

    cancelmsg.infotext = L"Just Choose Yes Or No, If You Dont I'll Teabag You.";
    cancelmsg.captionstring = L"British Pastime";
    cancelmsg.flags = MB_ICONINFORMATION | MB_OK;
    cancelmsg.setcall(last_str, cancelmsg.lastmsg);

    end.infotext = L"This Is The End";
    end.captionstring = L"My Only Friend";
    end.flags = MB_ICONEXCLAMATION | MB_OK;

    //perform loop service
    msghandlerbase * tmp = start.perform_message();
    while(tmp != NULL)
    {
        tmp = tmp->perform_message();
    }
    DialogBox(hInstance, "GAMEDIALOG", NULL, (DLGPROC)gamedialogproc);
    end.perform_message();
    cout << end.msgc;
    WCHAR messageobjectmsgc[100];
    wsprintfW(messageobjectmsgc, L"%d  %d", end.msgc, (INT_PTR)hInstance);
    MessageBoxW(NULL, messageobjectmsgc, L"message-object msg_count", 0);
    return 0;
}

class gamemessageobjectcontainer
{
public:
    msghandlerbase start;
    msghandlerbase exploretown;
    gamemessageobjectcontainer()
        {
            start = msghandlerbase();
            start.captionstring = L"MUCH BETTER";
            start.infotext = L"Now isn't this better?";
            start.setstringforcall(L"Fuck Yeah", no_str);
            start.setcall(no_str, &exploretown);
            exploretown = msghandlerbase();
            exploretown.captionstring = L"So where to?";
            exploretown.infotext = L"nullsville";
            exploretown.setstringforcall(L"END ME NOW", no_str);
            //exploretown.setcall(no_str, &exploretown);
        }
};
gamemessageobjectcontainer gmoh = gamemessageobjectcontainer();

BOOL CALLBACK gamedialogproc (HWND hDlg, unsigned int message, WPARAM wParam, LPARAM lParam)
{
    static msghandlerbase * currentmsg;
    switch (message)
    {
    case WM_INITDIALOG:
        setdialog(hDlg, &gmoh.start);
        currentmsg = &gmoh.start;
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD (wParam))
        {
        case IDOK:
        case IDNO:
        case IDYES:
            currentmsg = currentmsg->handle_message(LOWORD (wParam));
            if (currentmsg == NULL)EndDialog (hDlg, 0);
            else setdialog(hDlg, currentmsg);
            break;
        case IDCANCEL:
            EndDialog (hDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;

}

void setdialog(HWND hDlg, msghandlerbase * msghb)
{
    HWND htmp;
    SetWindowTextW(hDlg, msghb->captionstring.c_str());
    ShowWindow (GetDlgItem (hDlg, IDYES), SW_HIDE);
    ShowWindow (GetDlgItem (hDlg, IDNO), SW_HIDE);
    ShowWindow (GetDlgItem (hDlg, IDOK), SW_HIDE);
    ShowWindow (GetDlgItem (hDlg, 1002), SW_HIDE);
    ShowWindow (GetDlgItem (hDlg, 1001), SW_HIDE);
    ShowWindow (GetDlgItem (hDlg, 1000), SW_SHOWNORMAL);
    SetWindowTextW (GetDlgItem (hDlg, 1000), msghb->infotext.c_str());
    if(msghb->yesstrbool)
    {
        htmp = GetDlgItem (hDlg, IDYES);
        SetWindowTextW (htmp, msghb->altstringforyes.c_str());
        ShowWindow (GetDlgItem (hDlg, IDYES), SW_SHOWNORMAL);
    }
    if(msghb->nostrbool)
    {
        htmp = GetDlgItem (hDlg, IDNO);
        SetWindowTextW (htmp, msghb->altstringforno.c_str());
        ShowWindow (GetDlgItem (hDlg, IDNO), SW_SHOWNORMAL);
    }
    if(msghb->okstrbool)
    {
        htmp = GetDlgItem (hDlg, IDOK);
        SetWindowTextW (htmp, msghb->altstringforok.c_str());
        ShowWindow (GetDlgItem (hDlg, IDOK), SW_SHOWNORMAL);
    }
}
