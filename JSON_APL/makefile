SAMPLE:=JSON_APL
include makefile.win.64
MK_OPT:=$(if $(MK_OPT),$(MK_OPT),opt)
include makefile.common

CALLER:=call_$(SAMPLE)

vpath %.c $(SAMPLE)/$(SAMPLE) $(SAMPLE)/$(CALLER)
vpath %.cpp $(SAMPLE)/$(SAMPLE) $(SAMPLE)/$(CALLER)
vpath %.rc $(SAMPLE)/$(SAMPLE) $(SAMPLE)/$(CALLER)
vpath %.dyalog $(SAMPLE)/$(SAMPLE) $(SAMPLE)/$(CALLER)
vpath %.dws $(SAMPLE)/$(SAMPLE) $(SAMPLE)/$(CALLER)

INCS:=$(INCS) -I$(SAMPLE)/$(SAMPLE)/include -I$(SAMPLE)/$(SAMPLE)

APL_OBJDIR=$(SAMPLE)/obj/$(SAMPLE)/${MK_PORT}/${MK_BITS}/${MK_OPT}
EXE_OBJDIR=$(SAMPLE)/obj/$(CALLER)/${MK_PORT}/${MK_BITS}/${MK_OPT}

export C_FLAGS:=$(C_FLAGS) $(INCS)  ${INCS_${MK_PORT}}

EXENAME=$(CALLER)$(EXEEXT)
IMPLIBNAME=$(SAMPLE)
DLLNAME=lib$(IMPLIBNAME)
target: EXE

APL_SOURCES:=$(SAMPLE)
EXE_SOURCES:=$(CALLER)

APL_OBJS:=${addsuffix $(OBJEXT),${basename ${APL_SOURCES}}} # replace .* with .o
APL_OBJS:=$(APL_OBJS:%=$(APL_OBJDIR)/%)          # add the path on the front

EXE_OBJS:=${addsuffix $(OBJEXT),${basename ${EXE_SOURCES}}} # replace .* with .o
EXE_OBJS:=$(EXE_OBJS:%=$(EXE_OBJDIR)/%)          # add the path on the front

DWA_LIBS:=$(DWA_LIBDIR)/dwa_static$(LIBEXT) $(DWA_LIBDIR)/libdyalog$(LIBEXT)

ifeq ($(MK_PORT),win)
	EXE_LIBS:=$(APL_OBJDIR)/$(DLLNAME)${IMPLIBEXT}
else
	EXE_LIBS:=$(APL_OBJDIR)/$(DLLNAME)${IMPLIBEXT}
endif

$(APL_OBJDIR)/%$(OBJEXT): %.c
	@mkdir -p $(APL_OBJDIR)
	@$(CC) $(C_FLAGS) $(APL_C_FLAGS)  $(CC_OUTFILE)$@  $<

$(APL_OBJDIR)/%$(OBJEXT): %.cpp
	@mkdir -p $(APL_OBJDIR)
	@$(CC) $(C_FLAGS) $(APL_C_FLAGS)  $(CC_OUTFILE)$@  $<

$(EXE_OBJDIR)/%$(OBJEXT): %.c
	@mkdir -p $(EXE_OBJDIR)
	@$(CC) $(C_FLAGS)  $(CC_OUTFILE)$@  $<

$(EXE_OBJDIR)/%$(OBJEXT): %.cpp
	@mkdir -p $(EXE_OBJDIR)
	@$(CC) $(C_FLAGS)  $(CC_OUTFILE)$@  $<

$(APL_OBJDIR)/%$(RESEXT): %.rc  %.dyalog
	@mkdir -p $(APL_OBJDIR)
	@$(RC) $(R_FLAGS) /Fo$@  $(INCS)  $<

$(APL_OBJDIR)/%$(RESEXT): %.rc  %.dws
	@mkdir -p $(APL_OBJDIR)
	@$(RC) $(R_FLAGS) /Fo$@  $(INCS)  $<

$(APL_OBJDIR)/$(DLLNAME)${DLLEXT}: ${APL_OBJS} $(APL_OBJDIR)/$(SAMPLE)$(RESEXT)
	@$(LD) $(APL_OBJS) $(APL_OBJDIR)/$(SAMPLE)$(RESEXT) $(L_FLAGS) $(DWA_LIBS) $(LIBS) $(APL_L_FLAGS) $(LD_OUTFILE)$@

$(EXE_OBJDIR)/$(EXENAME): ${EXE_OBJS} $(APL_OBJDIR)/$(DLLNAME)${DLLEXT}
	@cp $(APL_OBJDIR)/$(DLLNAME)${DLLEXT} $(EXE_OBJDIR)
	@if [ -f $(APL_OBJDIR)/$(DLLNAME)${LIBEXT} ] ; then cp $(APL_OBJDIR)/$(DLLNAME)${LIBEXT} $(EXE_OBJDIR) ; fi
	@( cd $(EXE_OBJDIR) ; $(LD) $(notdir $(EXE_OBJS)) $(notdir $(EXE_LIBS)) $(LIBS) $(L_FLAGS) $(LD_OUTFILE)$(notdir $@) )
	@$(SET_RPATH) -change "$(APL_OBJDIR)/$(DLLNAME)$(DLLEXT)" "@loader_path/./$(DLLNAME)$(DLLEXT)" $(EXE_OBJDIR)/$(EXENAME)


APL: $(APL_OBJDIR)/$(DLLNAME)${DLLEXT}
EXE: $(EXE_OBJDIR)/$(EXENAME)

QA: EXE
	@$(EXE_OBJDIR)/$(EXENAME)
	@cd $(EXE_OBJDIR); ./$(EXENAME)
	


