include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}/../..
   ${CMAKE_BINARY_DIR}/okular
)

########### next target ###############

set(okularGenerator_rfc_SRCS
   generator_rfc.cc
   converter.cc
)


kde4_add_plugin(okularGenerator_rfc ${okularGenerator_rfc_SRCS})

target_link_libraries(okularGenerator_rfc okularcore ${KDE4_KDECORE_LIBS} ${KDE4_KDEUI_LIBS} ${QT_QTGUI_LIBRARY})

install(TARGETS okularGenerator_rfc DESTINATION ${PLUGIN_INSTALL_DIR})


########### install files ###############

install(FILES libokularGenerator_rfc.desktop okularRfc.desktop  DESTINATION  ${SERVICES_INSTALL_DIR})
