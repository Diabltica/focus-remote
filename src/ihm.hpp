//
// Created by thoma on 18/08/2022.
//

#ifndef FOCUS_REMOTE_IHM_HPP
#define FOCUS_REMOTE_IHM_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class IHM;
}
QT_END_NAMESPACE

class IHM : public QWidget
{
    Q_OBJECT

  public:
    explicit IHM(QWidget* parent = nullptr);
    ~IHM() override;

  private:
    Ui::IHM* ui;
};

#endif // FOCUS_REMOTE_IHM_HPP
