#ifndef joypad_H
#define joypad_H

#include <QDebug>
#include <QTimer>
#include <QWidget>
#include <SDL/SDL.h>
#include <assert.h>
//-----------------------------------------------------------//
///
/// Class for geting and interpreting joypad input using SDL library.
/// Starts when user selects joypad. RefreshTimer updates joypad state
/// and emits signal for pressed buttons or axes with function code
/// based on JoypadSettings. Also interprets key function and makes changes
/// to speed and heading in base class Controller. For more info
/// look at Controller class.
///
class JoypadController: public QWidget
{
  Q_OBJECT
public:
  explicit JoypadController(QWidget *parent = 0);
  ~JoypadController();

public slots:
  void refreshJoypadState(); /**< Reads data from joypad, must be done in time intervals */

  void setJoypad(int jsNumber);

signals:
  void buttonChanged(int index, bool state); /**< Used by configuration widget to change button functions */
  void axisChanged(int index, qint16 value); /**< Used by configuration widget to change axis functions */

private:
  QList<qint16> axes;
  QList<bool> buttons;
  QList<qint16> axesPrevious; /**< Holds previous state to check changes in axes */
  QList<bool> buttonsPrevious; /**< Holds previous state to check changes in buttons */

  SDL_Joystick* m_joypad; /**< SDL library struct, holding info about selected joypad */
  QTimer *refreshTimer; /**< After selecting joypad this timer starts and updates joypad state */

};

#endif // joypad_H
