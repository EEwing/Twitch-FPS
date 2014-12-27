SOURCE_DIR=./src/
SOURCES=$(addprefix $(SOURCE_DIR),Main.cxx Player.cxx Vector.cxx KeyboardHandler.cxx MouseHandler.cxx Button.cxx Gui/Gui.cxx Gui/GuiHandler.cxx RenderUtils.cxx)

CFLAGS=-g
LIBS=-lSOIL -lopengl32 -lfreeglut -lglu32 -lglew32
INCLUDE=-I$(SOURCE_DIR)
EXECUTABLE=fps

all:
	g++ $(SOURCES) $(CFLAGS) $(INCLUDE) -o $(EXECUTABLE) $(LIBS)