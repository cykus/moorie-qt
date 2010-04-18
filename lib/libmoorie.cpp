#include "libmoorie.h"


Libmoorie::Libmoorie()
{
    QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));
    QTextCodec::setCodecForCStrings ( QTextCodec::codecForName ("UTF-8"));
    QTextCodec::setCodecForLocale ( QTextCodec::codecForName ("UTF-8"));
}
QString Libmoorie::hello()
{
    return "Hej biblioteka działa!";
}
