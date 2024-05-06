#include "company.h"

Company::Company() : companyInfo() {}

Company::~Company() {
    companyInfo.clear();
}

QList <QString> Company::getCompanyInfo() {
    return companyInfo;
}

void Company::setCompanyInfo(QList <QString> &tmp) {
    companyInfo = tmp;
}
