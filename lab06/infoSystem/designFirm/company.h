#ifndef COMPANY_H
#define COMPANY_H

#include <QString>
#include <QList>

class Company
{
public:
    Company();
    ~Company();

public:
    QList <QString> getCompanyInfo();
    void setCompanyInfo(QList <QString>&);

protected:
    QList <QString> companyInfo;
    //QVector <QString> companyProjects;
    //QVector <QString> employees;
};

#endif // COMPANY_H
