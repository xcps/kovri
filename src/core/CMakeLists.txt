set(CORE_SRC
  "tunnel/TunnelConfig.cpp"
  "Garlic.cpp"
  "I2NPProtocol.cpp"
  "Identity.cpp"
  "LeaseSet.cpp"
  "NetDbRequests.cpp"
  "NetworkDatabase.cpp"
  "Profiling.cpp"
  "Reseed.cpp"
  "RouterContext.cpp"
  "RouterInfo.cpp"
  "crypto/AES.cpp"
  "crypto/CryptoConst.cpp"
  "crypto/EdDSA25519.cpp"
  "crypto/ElGamal.cpp"
  "crypto/Rand.cpp"
  "crypto/Signature.cpp"
  "crypto/Tunnel.cpp"
  "transport/NTCP.cpp"
  "transport/NTCPSession.cpp"
  "transport/SSU.cpp"
  "transport/SSUData.cpp"
  "transport/SSUSession.cpp"
  "transport/Transports.cpp"
  "transport/UPnP.cpp"
  "tunnel/TransitTunnel.cpp"
  "tunnel/Tunnel.cpp"
  "tunnel/TunnelEndpoint.cpp"
  "tunnel/TunnelGateway.cpp"
  "tunnel/TunnelPool.cpp"
  "util/Base64.cpp"
  "util/HTTP.cpp"
  "util/Log.cpp"
  "util/MTU.cpp"
  "util/Filesystem.cpp")

set(EDDSA_SRC
  "crypto/ed25519/fe_0.cpp"
  "crypto/ed25519/fe_1.cpp"
  "crypto/ed25519/fe_add.cpp"
  "crypto/ed25519/fe_cmov.cpp"
  "crypto/ed25519/fe_copy.cpp"
  "crypto/ed25519/fe_frombytes.cpp"
  "crypto/ed25519/fe_invert.cpp"
  "crypto/ed25519/fe_isnegative.cpp"
  "crypto/ed25519/fe_isnonzero.cpp"
  "crypto/ed25519/fe_mul.cpp"
  "crypto/ed25519/fe_neg.cpp"
  "crypto/ed25519/fe_pow22523.cpp"
  "crypto/ed25519/fe_sq.cpp"
  "crypto/ed25519/fe_sq2.cpp"
  "crypto/ed25519/fe_sub.cpp"
  "crypto/ed25519/fe_tobytes.cpp"
  "crypto/ed25519/ge_add.cpp"
  "crypto/ed25519/ge_double_scalarmult.cpp"
  "crypto/ed25519/ge_frombytes.cpp"
  "crypto/ed25519/ge_madd.cpp"
  "crypto/ed25519/ge_msub.cpp"
  "crypto/ed25519/ge_p1p1_to_p2.cpp"
  "crypto/ed25519/ge_p1p1_to_p3.cpp"
  "crypto/ed25519/ge_p2_0.cpp"
  "crypto/ed25519/ge_p2_dbl.cpp"
  "crypto/ed25519/ge_p3_0.cpp"
  "crypto/ed25519/ge_p3_dbl.cpp"
  "crypto/ed25519/ge_p3_to_cached.cpp"
  "crypto/ed25519/ge_p3_to_p2.cpp"
  "crypto/ed25519/ge_p3_tobytes.cpp"
  "crypto/ed25519/ge_precomp_0.cpp"
  "crypto/ed25519/ge_scalarmult_base.cpp"
  "crypto/ed25519/ge_sub.cpp"
  "crypto/ed25519/ge_tobytes.cpp"
  "crypto/ed25519/keypair.cpp"
  "crypto/ed25519/open.cpp"
  "crypto/ed25519/sc_muladd.cpp"
  "crypto/ed25519/sc_reduce.cpp"
  "crypto/ed25519/sign.cpp")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  list(APPEND CORE_SRC "util/I2PEndian.cpp")
endif()

include_directories(
  "."
  "../")

set(EDDSA_LIB "ed25519-ref10")
add_subdirectory(crypto/ed25519)

# Library building
if(WITH_LIBRARY)
  add_library(${CORE_NAME} ${CORE_SRC} ${EDDSA_SRC})
  target_link_libraries(
    ${CORE_NAME}
    ${Boost_LIBRARIES} ${CRYPTO++_LIBRARIES} ${OPENSSL_LIBRARIES}
    ${DL_LIB})
  install(
    TARGETS ${CORE_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

# vim: noai:ts=2:sw=2
