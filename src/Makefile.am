noinst_HEADERS = BaseApplication.h Game.h Physics.h Player.h Sound.h GameObject.h EntityObject.h PhysicsObject.h MotionState.h Sound.h BulletContactCallback.h NetManager.h DebugDraw.hpp DynamicLineDrawer.hpp

bin_PROGRAMS = downtale
downtale_CPPFLAGS = -I$(top_srcdir)
downtale_SOURCES = BaseApplication.cpp Game.cpp Physics.cpp Player.cpp Sound.cpp GameObject.cpp EntityObject.cpp PhysicsObject.cpp NetManager.cpp DebugDraw.cpp DynamicLineDrawer.cpp
downtale_CXXFLAGS = $(OGRE_CFLAGS) $(OIS_CFLAGS) $(bullet_CFLAGS) $(CEGUI_CFLAGS)
downtale_LDADD = $(OGRE_LIBS) $(OIS_LIBS) $(bullet_LIBS) $(CEGUI_LIBS) $(CEGUI_OGRE_LIBS)
downtale_LDFLAGS = -lOgreOverlay -lboost_system

EXTRA_DIST = buildit makeit
AUTOMAKE_OPTIONS = foreign

downtale_CPPFLAGS += -std=c++11
downtale_CPPFLAGS += -I/usr/include/SDL
downtale_LDFLAGS += -lSDL -lSDL_mixer -lSDL_net

downtale_LDFLAGS += -R/lusr/lib/cegui-0.8