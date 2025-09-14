#include <QApplication>

#include <MainController.h>
#include <QtView.h>


int main(int argc, char ** argv)
{
  QApplication app(argc, argv);

  QtView window;
  window.setWindowTitle("PrimiSketch");
  window.resize(800, 600);
  window.show();

  std::shared_ptr<IView> view(&window, [](IView *) {});
  std::shared_ptr<MainController> controller = std::make_shared<MainController>(view);
  view->AddEventListener(controller);

  return app.exec();
}
