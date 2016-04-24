noinst_HEADERS = BaseApplication.h Game.h Physics.h Player.h Sound.h GameObject.h EntityObject.h PhysicsObject.h MotionState.h Sound.h BulletContactCallback.h NetManager.h DebugDraw.hpp DynamicLineDrawer.hpp

bin_PROGRAMS = a
a_CPPFLAGS = -I$(top_srcdir)
a_SOURCES = BaseApplication.cpp Game.cpp Physics.cpp Player.cpp Sound.cpp GameObject.cpp EntityObject.cpp PhysicsObject.cpp NetManager.cpp DebugDraw.cpp DynamicLineDrawer.cpp
a_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(CEGUI_CFLAGS)
a_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(CEGUI_LIBS) $(CEGUI_OGRE_LIBS)
a_LDFLAGS = -lOgreOverlay -lboost_system

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign

a_CPPFLAGS += -std=c++11
a_CPPFLAGS += -I/usr/include/SDL
a_LDFLAGS += -lSDL -lSDL_mixer -lSDL_net

a_LDFLAGS += -R/lusr/lib/cegui-0.8