#include "joypadcontroller.h"
JoypadController::JoypadController(QWidget *parent) :
    QWidget(parent)
{
  m_joypad = NULL;
  refreshTimer = new QTimer(this);

  connect(refreshTimer,SIGNAL(timeout()),this,SLOT(refreshJoypadState()));
}
JoypadController::~JoypadController(){
  if (m_joypad != NULL){
    SDL_JoystickClose(m_joypad);
  }
}

void JoypadController::refreshJoypadState()
{
  if(m_joypad == NULL){
    return;
  }

  SDL_JoystickUpdate();

  axesPrevious = QList<qint16>(axes);
  buttonsPrevious = QList<bool>(buttons);

  axes.clear();
  buttons.clear();

  //Read all axis values
  for(int i=0;i<SDL_JoystickNumAxes(m_joypad);i++){
    axes.append(SDL_JoystickGetAxis(m_joypad,i));
  }

  //Read all buttons values
  for(int i=0;i<SDL_JoystickNumButtons(m_joypad);i++){
    buttons.append(SDL_JoystickGetButton(m_joypad,i));
  }

  //Check if there are some changes and emit signals
  if(axesPrevious.size() == axes.size()){
    for(int i=0 ; i<axes.size() ; i++){
      if(axesPrevious[i] != axes[i]){
        emit axisChanged(i,axes[i]);
      }
    }
  }
  if(buttonsPrevious.size() == buttons.size()){
    for(int i=0 ; i<buttons.size() ; i++){
      if(buttonsPrevious[i] != buttons[i]){
        emit buttonChanged(i,buttons[i]);
      }
    }
  }
  return;
}

//Opens joypad given by number js if not "-1", and closes previous one
void JoypadController::setJoypad(int js){
  refreshTimer->stop();
  assert(js < SDL_NumJoysticks());
  assert(js >= -1);

  if (m_joypad != NULL){
    SDL_JoystickClose(m_joypad);
    m_joypad = NULL;
  }
  else if(js == -1)
    return;

  if(js != -1){
    m_joypad = SDL_JoystickOpen(js);
    refreshTimer->start(50);
  }
}


