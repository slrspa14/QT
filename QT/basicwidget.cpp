#include "widget.h"

Widget::Widget(QWidget *parent) 
    : QWidget(parent)
{
    QString str1[3] = {"Game", "Office", "Develop"};
    QString str2[3] = {"P&rogramming", "Q&t", "O&S"};

    int xpos = 30;//
    int ypos = 30;//

    // 그룹분리, 분리시켜서 각자의 그룹에 영향받지 않음
    chk_group[0] = new QButtonGroup(this);
    chk_group[1] = new QButtonGroup(this);

    for(int i = 0 ; i < 3 ; i++)
    {
        exclusive[i] = new QCheckBox(str1[i], this); // 1그룹 체크박스 생성 체크박스 항목, 부모클래스
        exclusive[i]->setGeometry(xpos, ypos, 100, 30);//좌표, 크기
        chk_group[0]->addButton(exclusive[i]); //체크박스 그룹추가하기

        non_exclusive[i] = new QCheckBox(str2[i], this); // 2그룹 체크박스 생성 체크박스 항목, 부모클래스
        non_exclusive[i]->setGeometry(xpos + 120, ypos, 100, 30);
        chk_group[1]->addButton(non_exclusive[i]);

        connect(exclusive[i], SIGNAL(clicked()), this, SLOT(chkChanged())); //연결함수 클릭받은 오브젝트, 시그널, 신호 보내줄 오브젝트 이름 this(객체 자신을 가리키는 포인터), 시그널 발생시 호출할 슬롯함수

        ypos += 40;
    }
    //setExclusive 여러개의 체크박스 중 한 개만 선택가능 다른거 선택시 기존에 선택한 체크박스 해제 후 선택된다
    chk_group[0]->setExclusive(false);//다중 선택 가능
    chk_group[1]->setExclusive(true);// 다중 선택 불가능

    //아이콘삽입
    exclusive[0]->setIcon(QIcon(":resources/browser.png"));
    exclusive[1]->setIcon(QIcon(":resources/calendar.png"));
    exclusive[2]->setIcon(QIcon(":resources/chat.png"));

    non_exclusive[0]->setIcon(QIcon(":resources/editor.png"));
    non_exclusive[1]->setIcon(QIcon(":resources/mail.png"));
    non_exclusive[2]->setIcon(QIcon(":resources/users.png"));
}

void Widget::chkChanged()
{
    for(int i = 0 ; i < 3 ; i++)
    {
        if(exclusive[i]->checkState())
        {
            qDebug("checkbox %d selected ", i+1);
        }
    }
}

Widget::~Widget()
{

}

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("QComboBox");// 이름

    combo = new QComboBox(this); //combobox 생성(부모클래스)
    combo->setGeometry(50, 50, 200, 30); //x,y좌표 콤보박스 크기

    combo->addItem(QIcon(":resources/browser.png"), "Application"); //아이콘 삽입 및 글씨 삽입
    combo->addItem(QIcon(":resources/browser.png"), "Graphics");
    combo->addItem("Database");
    combo->addItem("Network");

    connect(combo, SIGNAL(currentIndexChanged(int)), // 연결함수 오브젝트 이름, 시그널, 디스, 시그널과 연결된 슬롯함수
            this,  SLOT(valueChanged()));

    QString str;
    str = combo->currentText();

    qDebug("Total Items : %d", combo->count());
}

void Widget::valueChanged()
{
    int current_index = combo->currentIndex();
    qDebug("Current ComboBox index : %d", current_index);
}

Widget::~Widget() // 소멸자
{
}

//qpushbutton이랑 동일기능 제공 windows link button 같은 스타일 제공
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(QSize(300, 100));

    cmmBtn = new QCommandLinkButton("Vision", "Vision Project", this);
    cmmBtn->setFlat(true);

    connect(cmmBtn, SIGNAL(clicked()), this, SLOT(clickFunc()));
}

void Widget::clickFunc()
{
    qDebug("QCommandLinkButton Click.");
}

Widget::~Widget()
{
}
//날짜표시 및 변경 gui
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    QDate dt1 = QDate(2020, 1, 1); //날짜 지정
    QDate dt2 = QDate::currentDate(); // 현재날짜

    dateEdit[0] = new QDateEdit(dt1.addYears(2), this); //생성
    dateEdit[0]->setGeometry(10, 10, 140, 40);

    dateEdit[1] = new QDateEdit(dt1.addMonths(3), this);
    dateEdit[1]->setGeometry(160, 10, 140, 40);

    dateEdit[2] = new QDateEdit(dt1.addDays(10), this);
    dateEdit[2]->setGeometry(310, 10, 140, 40);

    dateEdit[3] = new QDateEdit(dt2, this);
    dateEdit[3]->setGeometry(10, 60, 140, 40);

    // 1:mon, 2:tue, 3:wed, 4:thur, 5:fri, 6:sat, 7:sun
    //qDebug 디버깅 툴 얘가 출력함
    qDebug("Day of year : %d", dt1.dayOfYear()); 
    qDebug("End Day : %d", dt1.daysInMonth());
    qDebug("End Day : %d", dt1.daysInYear());

    QDate dt3 = QDate::fromString("2002.06.26", "yyyy.MM.dd"); //지정
    QDate dt4 = QDate::fromString("06.26", "MM.dd");

    lbl[0] = new QLabel(dt3.toString(), this);//생성
    lbl[0]->setGeometry(10,110, 150, 30);
    lbl[1] = new QLabel(dt4.toString(), this);
    lbl[1]->setGeometry(10,150, 150, 30);

    if(QDate::isValid(2011, 6, 27)) //인덱스 유효시 true 반환 아니라면 false 반환 유효 인덱스 모델에 속하며 음수가 아닌 행 및 열 번호를 갖는다 
    //없는 날짜면 펄스 뱉음
    {
        qDebug("2013.6.27 true");
    }
    else
    {
        qDebug("2013.6.27 false");
    }

    QDate dt5 = QDate(2012, 4, 26);

    QString LongWeek = dt5.longDayName(dt5.dayOfWeek());
    QString LongMonth = dt5.longMonthName(dt5.month());
    QString strDateLong = QString("%1 %2").arg(LongWeek).arg(LongMonth);

    QString ShortWeek = dt5.shortDayName(dt5.dayOfWeek());
    QString ShortMonth = dt5.shortMonthName(dt5.month());
    QString strDateShort = QString("%1 %2").arg(ShortWeek).arg(ShortMonth);


    lbl[2] = new QLabel(QString("Long: %1 , Short : %2").arg(strDateLong)
                                        .arg(strDateShort), this);
    lbl[2]->setGeometry(10, 190, 250, 30);

    QDate dt6 = QDate(2012, 7, 26);
    lbl[3] = new QLabel(dt6.toString(Qt::TextDate), this); //목 7월 26 2012공 //디폴트 타입
    lbl[3]->setGeometry(10, 240, 250, 30);

    lbl[4] = new QLabel(dt6.toString(Qt::ISODate), this);// 2012-07-26 //iso 확장 포맷 표시
    lbl[4]->setGeometry(10, 270, 250, 30);

    lbl[5] = new QLabel(dt6.toString(Qt::SystemLocaleDate), this);//12.7.26 // 국가 표현 방식 표시
    lbl[5]->setGeometry(10, 300, 250, 30);

}

Widget::~Widget()
{

}

//현재 시스템 설정 시간과 현재 시간으로부터 특정 시간까지의 경과 시간을 표시 시간을 비교함
//qtimeedit은 qtime 클래스로부터 얻어온 시간을 gui 인터페이스에 표시할 수 있는 기능제공
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    QTimeEdit *qte[10];

    QTime ti1 = QTime(6, 24, 0, 0); // hour, min, sec, millisecond //시간설정

    qte[0] = new QTimeEdit(ti1, this); //빈 시간 편집기 생성(qtime으로 구한 시간, 객체 자신)
    qte[0]->setGeometry(10, 30, 150, 30);

    QTime t;
    t = ti1.addSecs(70);
    qte[1] = new QTimeEdit(t, this);
    qte[1]->setGeometry(10, 70, 150, 30);

    qte[2] = new QTimeEdit(ti1.addSecs(2), this);
    qte[2]->setGeometry(10, 110, 150, 30);


    QTime ti2 = QTime::currentTime();

    qte[4] = new QTimeEdit(ti2.currentTime(), this);
    qte[4]->setGeometry(10, 150, 150, 30);


    QTime ti3;
    ti3.start();

    for(int i = 0 ; i < 100000 ; i++) {
        for(int j = 0 ; j < 10000 ; j++)     {
        }
    }

    qDebug("Elapsed Time : %d", ti3.elapsed());

    QTime ti4 = QTime::fromString("03:32", "hh:mm");

    QLabel *lbl_fromString = new QLabel(ti4.toString(), this);
    lbl_fromString->setGeometry(10, 190, 150, 30);

    QTime ti5 = QTime(6, 25, 34, 323);
    qDebug("Hour : %d", ti5.hour());
    qDebug("min : %d", ti5.minute());
    qDebug("sec : %d", ti5.second());
    qDebug("msec : %d", ti5.msec());

    QTime ti6 = QTime(7, 10, 23, 122);
    QLabel *lbl_toString = new QLabel(ti6.toString("AP hh:mm:ss:zzz"), this);
    lbl_toString->setGeometry(10, 10, 150, 30);

}

Widget::~Widget()
{

}
//qdatetime qdatetimeedit 날짜 시간을 함께 다룰 수 있는 클래스 qdatetimeedit 날짜 시간을 표시할 수 있는 gui 제공
//setDisplayFormat() 멤버함수임 포맷에 따라 날짜와 시간 표시 가능
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    QDateTimeEdit *qde1;
    qde1 = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    qde1->setDisplayFormat("yyyy-MM-dd hh:mm:ss:zzz");//표시방법 2024-01-25 19:00:??:???
    qde1->setGeometry(10, 30, 250, 30);

    QDateTimeEdit *qde[3];

    qde[0] = new QDateTimeEdit(QDate::currentDate(), this);
    qde[0]->setMinimumDate(QDate::currentDate().addYears(-3));// 최소 최대 범위지정 그 구간만 가능 -3 ~ +3
    qde[0]->setMaximumDate(QDate::currentDate().addYears(3));
    qde[0]->setDisplayFormat("yyyy");
    qde[0]->setGeometry(10, 90, 100, 30);

    qde[1] = new QDateTimeEdit(QDate::currentDate(), this);
    qde[1]->setMinimumDate(QDate::currentDate().addMonths(-2));
    qde[1]->setMaximumDate(QDate::currentDate().addMonths(2));
    qde[1]->setDisplayFormat("MM");
    qde[1]->setGeometry(120, 90, 100, 30);

    qde[2] = new QDateTimeEdit(QDate::currentDate(), this);
    qde[2]->setMinimumDate(QDate::currentDate().addDays(-20));
    qde[2]->setMaximumDate(QDate::currentDate().addDays(20));
    qde[2]->setDisplayFormat("dd");
    qde[2]->setGeometry(230, 90, 100, 30);

}

Widget::~Widget()
{
}
//dial
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    int xpos = 30;

    for(int i = 0 ; i < 3 ; i++, xpos += 110)
    {
        dial[i] = new QDial(this);
        dial[i]->setRange(0, 100);
        dial[i]->setGeometry(xpos, 30, 100, 100);
    }

    dial[0]->setNotchesVisible(true);//눈금표시 기본값 false
    connect(dial[0], &QDial::valueChanged, this, &Widget::changedData);
}

void Widget::changedData()
{
    qDebug("QDial 1 value : %d", dial[0]->value());
}

Widget::~Widget()
{

}

//qspinbox qdoublespinbox
//qspinbox int형 데이터 타입 정수 값을 상하 버튼을 이용해 변경가능한 gui제공 double은 doublespinbox
//범위 제한 가능, 숫자 표시되는 Prefix와 Suffix 부분에 특정 문자 혹은 단위를 가르키는 문자사용가능
#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    int ypos = 30;
    int val[3] = {50, 100, 200};
    double double_val[3] = {50.5, 127.32, 171.342};

    for(int i = 0 ; i < 3 ; i++)
    {
        spin[i] = new QSpinBox(this);//생성
        spin[i]->setMinimum(10);//최소
        spin[i]->setMaximum(300);//최대제한
        spin[i]->setValue(val[i]);//값 설정
        spin[i]->setGeometry(10, ypos, 100, 30); //좌표 및 크기설정

        doublespin[i] = new QDoubleSpinBox(this);
        doublespin[i]->setMinimum(10.0);
        doublespin[i]->setMaximum(300.0);
        doublespin[i]->setValue(double_val[i]);
        doublespin[i]->setGeometry(120, ypos, 100, 30);

        spin[i]->setPrefix("$ ");//특정 문자 삽입
        doublespin[i]->setSuffix(" mm"); // 단위 가리키는 문자 삽입

        ypos += 40;
    }

    connect(spin[0], SIGNAL(valueChanged(int)),
            this,    SLOT(valueChange()));

    connect(doublespin[0], SIGNAL(valueChanged(double)),
            this,          SLOT(double_valueChange()));

}

void Widget::valueChange()
{
    qDebug("Change value : %d", spin[0]->value());
}

void Widget::double_valueChange()
{
    qDebug("Change double value : %3.2f", doublespin[0]->value());
}

Widget::~Widget()
{

}

//qpushbutton qfocusframe은 바깥쪽에 outer line 사용시 쓴다

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("QPushButton"); //이름짓고

QPushButton *btn[3];

int ypos = 30;
for(int i = 0 ; i < 3 ; i++)
{
    /*pdf예제
    QString str = QString("Frame's button %1").arg(i);
    btn[i] = new QPushButton(str, this);첫번째 인자는 버튼에 표시할 텍스트 입력, 두번째 인자는 푸시버튼 클래스의 부모 클래스 지정*/
    btn[i] = new QPushButton(QString("Frame's button %1").arg(i), this);
    btn[i]->setGeometry(10, ypos, 300, 40);
    ypos += 50;
}

connect(btn[0], &QPushButton::clicked,  this, &Widget::btn_click);
connect(btn[0], &QPushButton::pressed,  this, &Widget::btn_pressed);
connect(btn[0], &QPushButton::released, this, &Widget::btn_released);

QFocusFrame *btn_frame = new QFocusFrame(this);
btn_frame->setWidget(btn[0]);
btn_frame->setAutoFillBackground(true);

}

void Widget::btn_click()
{
    qDebug("Button Click");
}

void Widget::btn_pressed()
{
    qDebug("Button Pressed");
}

void Widget::btn_released()
{
    qDebug("Button Relased");
}

Widget::~Widget()
{
}
//QFontComboBox GUI상에 폰트를 선택하기 위한 GUI를 제공 폰트 알파벳 순서로 나열 및 모양확인가능
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    
    QFontComboBox *fontcombo[5];
    for(int i = 0 ; i < 5 ; i++)
        fontcombo[i] = new QFontComboBox(this);
    
    fontcombo[0]->setFontFilters(QFontComboBox::AllFonts); //모든폰트
    fontcombo[1]->setFontFilters(QFontComboBox::ScalableFonts);//확대/축소시 동적 자동 변환 가능한 폰트
    fontcombo[2]->setFontFilters(QFontComboBox::NonScalableFonts);//동적 자동 변환이 제공되지 않는 폰트
    fontcombo[3]->setFontFilters(QFontComboBox::MonospacedFonts);//일정한 문자 넓이 형태를 제공하는 폰트
    fontcombo[4]->setFontFilters(QFontComboBox::ProportionalFonts);// 넓이와 폭의 균형이 잡힌 폰트
    
    int ypos = 30;
    for(int i = 0 ; i < 5 ; i++) {
        fontcombo[i]->setGeometry(10, ypos, 200, 30);
        ypos += 40;
    }
    
    lbl = new QLabel("I love Qt programming", this);
    lbl->setGeometry(10, ypos, 200, 30);
    
    connect(fontcombo[0], SIGNAL(currentIndexChanged(int)),
            this,         SLOT(changedIndex(int)));
    
    connect(fontcombo[0], SIGNAL(currentFontChanged(QFont)),
            this,         SLOT(changedFont(const QFont &)));
}

void Widget::changedIndex(int idx)
{
    qDebug("Font index : %d", idx);
}

void Widget::changedFont(const QFont &f)
{
    lbl->setFont(f.family());
}

Widget::~Widget()
{
    
}

//QLabel:텍스트 또는 이미지 표시하는 기능 제공 QLCDNumber: 숫자만 표시가능 디지털 시계같은 형태로 숫자표시가능 :문자 사용가능
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("QLabel and QLCDNumber Widget");

    QLabel  *lbl[3];
    lbl[0] = new QLabel("I love Qt programming", this);
    lbl[0]->setGeometry(10, 30, 130, 40);

    QPixmap pix = QPixmap(":resources/browser.png");//이미지 
    lbl[1] = new QLabel(this);
    lbl[1]->setPixmap(pix);//표시
    lbl[1]->setGeometry(10, 70, 100, 100);

    QLCDNumber *lcd[3];
    lcd[0] = new QLCDNumber(2, this);
    lcd[0]->display(24);
    lcd[0]->setGeometry(150, 30, 200, 100);
    lcd[0]->setSegmentStyle(QLCDNumber::Outline);//배경색으로 채워진 볼록한 세그먼트 생성

    lcd[1] = new QLCDNumber(5, this);
    lcd[1]->display("10:34");
    lcd[1]->setGeometry(150, 140, 200, 100);
    lcd[1]->setSegmentStyle(QLCDNumber::Filled);//전경색으로 채워진 볼록한 세그먼트 생성, 기본값임

    lcd[2] = new QLCDNumber(5, this);
    lcd[2]->display("10:34");
    lcd[2]->setGeometry(150, 250, 200, 100);
    lcd[2]->setSegmentStyle(QLCDNumber::Flat);//전경색으로 채워진 평면 세그먼트 생성

}

Widget::~Widget()
{

}

//qlineedit 텍스트 입력 및 수정을 위한 gui 제공 위젯상에서 복붙,자르기 가능
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    edit[0] = new QLineEdit("", this);
    lbl = new QLabel("QlineEdit Text : ", this);

    connect(edit[0], SIGNAL(textChanged(QString)),
            this,    SLOT(textChanged(QString)));

    edit[0]->setGeometry(10, 30, 200, 40);
    lbl->setGeometry(10, 80, 250, 30);

    int ypos = 120;
    for(int i = 1 ; i < 5 ; i++)
    {
        edit[i] = new QLineEdit("I love qt.", this);
        edit[i]->setGeometry(10, ypos, 200, 40);
        ypos += 50;
    }
    //setEchoMode 텍스트 안보이게 또는 패스워드 처리
    edit[1]->setEchoMode(QLineEdit::Normal); //디폴트와 동일 스타일
    edit[2]->setEchoMode(QLineEdit::NoEcho);//텍스트 안보임 커서 위치도 변경 안됨
    edit[3]->setEchoMode(QLineEdit::Password);//텍스트 *표시
    edit[4]->setEchoMode(QLineEdit::PasswordEchoOnEdit);// 텍스트가 변경되면 디폴트 스타일과 동일하지만 포커스가 이동되면 * 표시

}

void Widget::textChanged(QString str)
{
    lbl->setText(QString("QlineEdit Text : %1").arg(str));
}

Widget::~Widget()
{

}

//QMenu QMenuBar 메뉴 기능 제공
//QMenu 위젯은 메뉴를 만들기 위해 제공하는 위젯 addAction(), addMenu() 멤버함수 제공
//addAction()하위 메뉴 없이 바로 실행할 기능을 연결하기 위해 사용
//addMenu()하위 메뉴를 연결할 때 사용하는 멤버 함수
//qmenu 생성 -> qmenubar와 연결 -> 메뉴 완성
#include "widget.h"
/*
Widget::Widget(QWidget *parent) : QWidget(parent)
{
    menuBar = new QMenuBar(this);

    menu[0] = new QMenu("File");
    menu[0]->addAction("Edit");
    menu[0]->addAction("View");
    menu[0]->addAction("Tools");

    act[0] = new QAction("New", this);
    act[0]->setShortcut(Qt::CTRL | Qt::Key_A); //바로가기 키 설정?
    act[0]->setStatusTip("This is a New menu.");

    act[1] = new QAction("Open", this);
    act[1]->setCheckable(true);

    menu[1] = new QMenu("Save");
    menu[1]->addAction(act[0]);
    menu[1]->addAction(act[1]);

    menu[2] = new QMenu("Print");
    menu[2]->addAction("Page Setup");
    menu[2]->addMenu(menu[1]);

    menuBar->addMenu(menu[0]);
    menuBar->addMenu(menu[2]);


    lbl = new QLabel("",this);

    connect(menuBar, SIGNAL(triggered(QAction*)), this,
                     SLOT(trigerMenu(QAction*)));

    menuBar->setGeometry(0, 0, 600, 40);
    lbl->setGeometry(10, 200, 200, 40);
}

void Widget::trigerMenu(QAction *act)
{
    QString str = QString("Selected Menu : %1").arg(act->text());
    lbl->setText(str);
}

Widget::~Widget()
{

}
*/
//

//qprogressbar
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    progress[0] = new QProgressBar(this);
    progress[0]->setMinimum(0);
    progress[0]->setMaximum(100);
    progress[0]->setValue(50);
    progress[0]->setOrientation(Qt::Horizontal);
    //이제 사용되지 않음 새 코드에서는 사용하지 않는게 좋다
    //가로 혹은 세로 방향 표시

    progress[1] = new QProgressBar(this);
    progress[1]->setMinimum(0);
    progress[1]->setMaximum(100);
    progress[1]->setValue(70);
    progress[1]->setOrientation(Qt::Horizontal);
    progress[1]->setInvertedAppearance(true);//값이 반전되는지 기본값 false
    //true면 최소값과 최대값 위치 변경되서 출력

    progress[2] = new QProgressBar(this);
    progress[2]->setMinimum(0);
    progress[2]->setMaximum(100);
    progress[2]->setValue(50);
    progress[2]->setOrientation(Qt::Vertical);

    progress[3] = new QProgressBar(this);
    progress[3]->setMinimum(0);
    progress[3]->setMaximum(100);
    progress[3]->setValue(70);
    progress[3]->setOrientation(Qt::Vertical);
    progress[3]->setInvertedAppearance(true);

    progress[0]->setGeometry(10,30, 300, 30);
    progress[1]->setGeometry(10,70, 300, 30);

    progress[2]->setGeometry(400,30, 30, 300);
    progress[3]->setGeometry(440,30, 30, 300);
}

Widget::~Widget()
{

}

//radio button
//사용자에게 여러 항목 중 하나를 선택할 수 있는 gui 제공, on, off 둘 중 하나 선택가능
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    QRadioButton *radio1[3];
    QRadioButton *radio2[3];

    QString str1[3] = {"Computer", "Notebook", "Tablet"};

    int ypos = 30;
    for(int i = 0 ; i < 3 ; i++)
    {
        radio1[i] = new QRadioButton(str1[i], this);
        radio1[i]->setGeometry(10, ypos, 150, 30);

        ypos += 40;
    }

    QString str2[3] = {"In-Vehicle", "Smart TV", "Mobile"};

    ypos = 30;
    for(int i = 0 ; i < 3 ; i++)
    {
        radio2[i] = new QRadioButton(str2[i], this);
        if(i == 2)
            radio2[i]->setChecked(true);//버튼이 선택되었는지, 체크 가능한 버튼만 가능 기본적으로 버튼 선택x

        radio2[i]->setGeometry(180, ypos, 150, 30);

        ypos += 40;
    }

    //그룹분리
    QButtonGroup *group1 = new QButtonGroup(this);
    QButtonGroup *group2 = new QButtonGroup(this);

    group1->addButton(radio1[0]);
    group1->addButton(radio1[1]);
    group1->addButton(radio1[2]);

    group2->addButton(radio2[0]);
    group2->addButton(radio2[1]);
    group2->addButton(radio2[2]);


}

Widget::~Widget()
{

}

//qscrollarea 위젯보다 사진 클 때 스크롤바로 움직여서 보는거

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QImage image;
    QScrollArea *area;

    QLabel *lbl = new QLabel(this);

    image = QImage(":resources/fish.png"); //사진경로 지정

    lbl->setPixmap(QPixmap::fromImage(image));

    area = new QScrollArea(this);
    area->setWidget(lbl);
    area->setBackgroundRole(QPalette::Dark);

    area->setGeometry(0, 0, image.width(), image.height());
}

Widget::~Widget()
{

}
