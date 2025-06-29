ares_components(sh2 m68000)

ares_add_sources(
  CORE #
    saturn
  UNITY #
    saturn.cpp
  PRIMARY #
    system/system.cpp
)


ares_add_sources(
  CORE #
    saturn
  INCLUDED #
    saturn.hpp
    CMakeLists.txt
)

ares_add_sources(
  CORE #
    saturn
  INCLUDED #
    # system/controls.cpp 
    system/serialization.cpp
    system/system.hpp
)