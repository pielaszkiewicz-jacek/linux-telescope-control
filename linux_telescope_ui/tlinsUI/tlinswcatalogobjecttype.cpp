#include "tlinswcatalogobjecttype.h"
#include "tlinsuistylesmanager.h"
#include "ui_tlinswcatalogobjecttype.h"
#include <QDebug>

tlinsWCatalogObjectType::tlinsWCatalogObjectType(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::tlinsWCatalogObjectType)
{
    ui->setupUi(this);

    // Control styles
    std::string style;
    tlinsUiStylesManager::getStyle(tlinsUiStylesManager::CATALOG_ID_TYPE,
        tlinsUiStylesManager::FieldType::GROUP_BOX,
        style);
    connect(ui->catalogObjectId, SIGNAL(editingFinished()), this, SLOT(update()));
}

void tlinsWCatalogObjectType::disable()
{
    ui->catalogObjectId->setDisabled(true);
}

void tlinsWCatalogObjectType::setID(const std::string& id)
{
    ui->catalogObjectId->setText(QString(id.c_str()));
}

std::string tlinsWCatalogObjectType::getID() const
{
    return ui->catalogObjectId->text().toStdString();
}

void tlinsWCatalogObjectType::update()
{
    qDebug() << "void tlinsWObjectName:: update()";
    emit valueChanged(std::string(ui->catalogObjectId->text().toStdString()));
}

tlinsWCatalogObjectType::~tlinsWCatalogObjectType()
{
    delete ui;
}
