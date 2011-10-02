#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/test/test_pu_socket_client.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/test/test_pt_socket_server.o \
	${OBJECTDIR}/test/test_pt_socket_client.o \
	${OBJECTDIR}/test/test_pu_socket_server.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pandora1811-daemon

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pandora1811-daemon: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pandora1811-daemon ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/test/test_pu_socket_client.o: test/test_pu_socket_client.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/test_pu_socket_client.o test/test_pu_socket_client.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/test/test_pt_socket_server.o: test/test_pt_socket_server.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/test_pt_socket_server.o test/test_pt_socket_server.cpp

${OBJECTDIR}/test/test_pt_socket_client.o: test/test_pt_socket_client.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/test_pt_socket_client.o test/test_pt_socket_client.cpp

${OBJECTDIR}/test/test_pu_socket_server.o: test/test_pu_socket_server.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/test/test_pu_socket_server.o test/test_pu_socket_server.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pandora1811-daemon

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
