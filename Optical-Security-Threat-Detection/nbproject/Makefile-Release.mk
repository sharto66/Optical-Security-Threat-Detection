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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/BarrelDetection.o \
	${OBJECTDIR}/InputImage.o \
	${OBJECTDIR}/ProcessingMethods.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m32
CXXFLAGS=-m32

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=--64

# Link Libraries and Options
LDLIBSOPTIONS=-L../../../../opencv/release/lib -lopencv_calib3d300.dll -lopencv_calib3d_pch_dephelp -lopencv_core300.dll -lopencv_core_pch_dephelp -lopencv_features2d300.dll -lopencv_features2d_pch_dephelp -lopencv_flann300.dll -lopencv_flann_pch_dephelp -lopencv_hal300 -lopencv_hal_pch_dephelp -lopencv_highgui300.dll -lopencv_highgui_pch_dephelp -lopencv_imgcodecs300.dll -lopencv_imgcodecs_pch_dephelp -lopencv_imgproc300.dll -lopencv_imgproc_pch_dephelp -lopencv_ml300.dll -lopencv_ml_pch_dephelp -lopencv_objdetect300.dll -lopencv_objdetect_pch_dephelp -lopencv_perf_calib3d_pch_dephelp -lopencv_perf_core_pch_dephelp -lopencv_perf_features2d_pch_dephelp -lopencv_perf_imgcodecs_pch_dephelp -lopencv_perf_imgproc_pch_dephelp -lopencv_perf_objdetect_pch_dephelp -lopencv_perf_photo_pch_dephelp -lopencv_perf_stitching_pch_dephelp -lopencv_perf_superres_pch_dephelp -lopencv_perf_video_pch_dephelp -lopencv_perf_videoio_pch_dephelp -lopencv_photo300.dll -lopencv_photo_pch_dephelp -lopencv_shape300.dll -lopencv_shape_pch_dephelp -lopencv_stitching300.dll -lopencv_stitching_pch_dephelp -lopencv_superres300.dll -lopencv_superres_pch_dephelp -lopencv_test_calib3d_pch_dephelp -lopencv_test_core_pch_dephelp -lopencv_test_features2d_pch_dephelp -lopencv_test_flann_pch_dephelp -lopencv_test_highgui_pch_dephelp -lopencv_test_imgcodecs_pch_dephelp -lopencv_test_imgproc_pch_dephelp -lopencv_test_ml_pch_dephelp -lopencv_test_objdetect_pch_dephelp -lopencv_test_photo_pch_dephelp -lopencv_test_shape_pch_dephelp -lopencv_test_stitching_pch_dephelp -lopencv_test_superres_pch_dephelp -lopencv_test_video_pch_dephelp -lopencv_test_videoio_pch_dephelp -lopencv_ts300 -lopencv_ts_pch_dephelp -lopencv_video300.dll -lopencv_video_pch_dephelp -lopencv_videoio300.dll -lopencv_videoio_pch_dephelp -lopencv_videostab300.dll -lopencv_videostab_pch_dephelp

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/optical-security-threat-detection.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/optical-security-threat-detection.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/optical-security-threat-detection ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/BarrelDetection.o: nbproject/Makefile-${CND_CONF}.mk BarrelDetection.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/opencv/build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BarrelDetection.o BarrelDetection.cpp

${OBJECTDIR}/InputImage.o: nbproject/Makefile-${CND_CONF}.mk InputImage.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/opencv/build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/InputImage.o InputImage.cpp

${OBJECTDIR}/ProcessingMethods.o: nbproject/Makefile-${CND_CONF}.mk ProcessingMethods.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/opencv/build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ProcessingMethods.o ProcessingMethods.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/C/opencv/build/include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/optical-security-threat-detection.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
