#include "../desktop-ui.hpp"
#include "cheats.cpp"
#include "manifest.cpp"
#include "memory.cpp"
#include "graphics.cpp"
#include "streams.cpp"
#include "properties.cpp"
#include "tracer.cpp"

namespace Instances { Instance<ToolsWindow> toolsWindow; }
ToolsWindow& toolsWindow = Instances::toolsWindow();
ManifestViewer& manifestViewer = toolsWindow.manifestViewer;
CheatEditor& cheatEditor = toolsWindow.cheatEditor;
MemoryEditor& memoryEditor = toolsWindow.memoryEditor;
GraphicsViewer& graphicsViewer = toolsWindow.graphicsViewer;
StreamManager& streamManager = toolsWindow.streamManager;
PropertiesViewer& propertiesViewer = toolsWindow.propertiesViewer;
TraceLogger& traceLogger = toolsWindow.traceLogger;

ToolsWindow::ToolsWindow(std::recursive_mutex *programMutex) {

  panelList.append(ListViewItem().setText("Manifest").setIcon(Icon::Emblem::Binary));
  panelList.append(ListViewItem().setText("Cheats").setIcon(Icon::Emblem::Text));

  // Cocoa hiro is missing the hex editor widget
  panelList.append(ListViewItem().setText("Memory").setIcon(Icon::Device::Storage));

  panelList.append(ListViewItem().setText("Graphics").setIcon(Icon::Emblem::Image));
  panelList.append(ListViewItem().setText("Streams").setIcon(Icon::Emblem::Audio));
  panelList.append(ListViewItem().setText("Properties").setIcon(Icon::Emblem::Text));
  panelList.append(ListViewItem().setText("Tracer").setIcon(Icon::Emblem::Script));
  panelList->setUsesSidebarStyle();
  panelList.onChange([&] { eventChange(); });

  panelContainer.setPadding(5_sx, 5_sy);
  panelContainer.append(manifestViewer, Size{~0, ~0});
  panelContainer.append(cheatEditor, Size{~0, ~0});
  panelContainer.append(memoryEditor, Size{~0, ~0});
  panelContainer.append(graphicsViewer, Size{~0, ~0});
  panelContainer.append(streamManager, Size{~0, ~0});
  panelContainer.append(propertiesViewer, Size{~0, ~0});
  panelContainer.append(traceLogger, Size{~0, ~0});
  panelContainer.append(homePanel, Size{~0, ~0});

  manifestViewer.construct();
  cheatEditor.construct(programMutex);
  memoryEditor.construct(programMutex);
  graphicsViewer.construct(programMutex);
  streamManager.construct();
  propertiesViewer.construct();
  traceLogger.construct();
  homePanel.construct();

  setDismissable();
  setTitle("Tools");
  setSize({700_sx, 405_sy});
  setAlignment({1.0, 1.0});
  setMinimumSize({480_sx, 320_sy});
}

auto ToolsWindow::show(const string& panel) -> void {
  for(auto& item : panelList.items()) {
    if(item.text() == panel) {
      item.setSelected();
      eventChange();
      break;
    }
  }
  setVisible();
  setFocused();
  panelList.setFocused();
}

auto ToolsWindow::eventChange() -> void {
  manifestViewer.setVisible(false);
  cheatEditor.setVisible(false);
  memoryEditor.setVisible(false);
  graphicsViewer.setVisible(false);
  streamManager.setVisible(false);
  propertiesViewer.setVisible(false);
  traceLogger.setVisible(false);
  homePanel.setVisible(false);

  bool found = false;
  if(auto item = panelList.selected()) {
    if(item.text() == "Manifest"  ) found = true, manifestViewer.setVisible();
    if(item.text() == "Cheats"    ) found = true, cheatEditor.setVisible();
    if(item.text() == "Memory"    ) found = true, memoryEditor.setVisible();
    if(item.text() == "Graphics"  ) found = true, graphicsViewer.setVisible();
    if(item.text() == "Streams"   ) found = true, streamManager.setVisible();
    if(item.text() == "Properties") found = true, propertiesViewer.setVisible();
    if(item.text() == "Tracer"    ) found = true, traceLogger.setVisible();
  }
  if(!found) homePanel.setVisible();

  panelContainer.resize();
}
