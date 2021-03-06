﻿#include "giftestdialog.h"
#include "ui_giftestdialog.h"
#include "qqtframe.h"

GifTestDialog::GifTestDialog ( QWidget* parent ) :
    QDialog ( parent ),
    ui ( new Ui::GifTestDialog )
{
    ui->setupUi ( this );

    //使用res函数以前，代码量如此巨大。
#if defined (__ANDROID__) || defined (__ANDROIDX86__)
#if 0
    //如果apk文件被删除了呢？
    ui->labelGif->setGifFile ( "assets:/waiting.gif" );
    ui->widgetGif->setGifFile ( "assets:/waiting.gif" );
    ui->widgetQQt->setPixmap ( "assets:/yun.png" );
#else
    ui->labelGif->setGifFile ( "://AppRoot/waiting.gif" );
    ui->widgetGif->setGifFile ( "://AppRoot/waiting.gif" );
    ui->widgetQQt->setPixmap ( "://AppRoot/yun.png" );
#endif
#else
    //不兼容android....
    ui->labelGif->setGifFile ( "./waiting.gif" );
    ui->widgetGif->setGifFile ( "./waiting.gif" );
    ui->widgetQQt->setPixmap ( "./yun.png" );
#endif

    //使用了res函数以后 代码得到了极大简化
    pline() << res ( "waiting.gif" );
    pline() << res ( "../waiting.gif" );
    pline() << QDir ( "." ).relativeFilePath ( "skin/yun.png" );
    pline() << QDir ( res ( "../waiting.gif" ) ).absolutePath();
    ui->labelGif->setGifFile (  skin ( "waiting.gif" ) );
    ui->widgetGif->setGifFile ( skin ( "waiting.gif" ) );
    ui->widgetQQt->setPixmap ( skin ( "yun.png" ) );

    pline() << QMovie::supportedFormats();
}

GifTestDialog::~GifTestDialog()
{
    delete ui;
}
