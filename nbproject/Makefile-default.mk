#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB_projet.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB_projet.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=init.c MI2C.c main.c motors.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/init.o ${OBJECTDIR}/MI2C.o ${OBJECTDIR}/main.o ${OBJECTDIR}/motors.o
POSSIBLE_DEPFILES=${OBJECTDIR}/init.o.d ${OBJECTDIR}/MI2C.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/motors.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/init.o ${OBJECTDIR}/MI2C.o ${OBJECTDIR}/main.o ${OBJECTDIR}/motors.o

# Source Files
SOURCEFILES=init.c MI2C.c main.c motors.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB_projet.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F2520
MP_PROCESSOR_OPTION_LD=18f2520
MP_LINKER_DEBUG_OPTION=-r=ROM@0x7DC0:0x7FFF -r=RAM@GPR:0x5F4:0x5FF -u_DEBUGSTACK
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/init.o: init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/init.o.d 
	@${RM} ${OBJECTDIR}/init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/init.o   init.c 
	@${DEP_GEN} -d ${OBJECTDIR}/init.o 
	@${FIXDEPS} "${OBJECTDIR}/init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/MI2C.o: MI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/MI2C.o.d 
	@${RM} ${OBJECTDIR}/MI2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/MI2C.o   MI2C.c 
	@${DEP_GEN} -d ${OBJECTDIR}/MI2C.o 
	@${FIXDEPS} "${OBJECTDIR}/MI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/motors.o: motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/motors.o.d 
	@${RM} ${OBJECTDIR}/motors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/motors.o   motors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/motors.o 
	@${FIXDEPS} "${OBJECTDIR}/motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/init.o: init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/init.o.d 
	@${RM} ${OBJECTDIR}/init.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/init.o   init.c 
	@${DEP_GEN} -d ${OBJECTDIR}/init.o 
	@${FIXDEPS} "${OBJECTDIR}/init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/MI2C.o: MI2C.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/MI2C.o.d 
	@${RM} ${OBJECTDIR}/MI2C.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/MI2C.o   MI2C.c 
	@${DEP_GEN} -d ${OBJECTDIR}/MI2C.o 
	@${FIXDEPS} "${OBJECTDIR}/MI2C.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/motors.o: motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/motors.o.d 
	@${RM} ${OBJECTDIR}/motors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/motors.o   motors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/motors.o 
	@${FIXDEPS} "${OBJECTDIR}/motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB_projet.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.47/bin/LKR/18f2520_g.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "C:\Program Files (x86)\Microchip\mplabc18\v3.47\bin\LKR\18f2520_g.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB_projet.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB_projet.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.47/bin/LKR/18f2520_g.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "C:\Program Files (x86)\Microchip\mplabc18\v3.47\bin\LKR\18f2520_g.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB_projet.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
