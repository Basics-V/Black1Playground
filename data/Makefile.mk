project_data = $(unpack_dir)/data

log_dir = $(build_dir)/logs

# Command definitions
java = java

# Tool definitions
CTRMap      = $(tools_dir)/CTRMap.jar
CTRMapV     = $(tools_dir)/CTRMapV.jar
pks_preproc = $(tools_dir)/pks_preprocessor.py
narc_tool   = $(tools_dir)/narc_tool.py

# Black1Playground data
playground_dir = $(project_data)/Black1Playground

# ARC Definitions
TEXT_SYSTEM_ARC = $(project_data)/a/0/0/2
TEXT_EVENTS_ARC = $(project_data)/a/0/0/3
FIELD_EVENT_ARC = $(project_data)/a/0/5/7

# Data Definitions
FIELD_EVENT_ROOT = $(data_dir)/scripting/scripts
TEXT_SYSTEM_ROOT = $(data_dir)/text/system
TEXT_EVENTS_ROOT = $(data_dir)/text/events

# Targets
TEXT_SYSTEM_FILES := $(patsubst $(TEXT_SYSTEM_ROOT)/%.txt, $(TEXT_SYSTEM_ARC)/%, $(wildcard $(TEXT_SYSTEM_ROOT)/*))
TEXT_EVENTS_FILES := $(patsubst $(TEXT_EVENTS_ROOT)/%.txt, $(TEXT_EVENTS_ARC)/%, $(wildcard $(TEXT_EVENTS_ROOT)/*))
FIELD_SCRIPTS     := $(patsubst $(FIELD_EVENT_ROOT)/%.pks, $(FIELD_EVENT_ARC)/%, $(wildcard $(FIELD_EVENT_ROOT)/*))

# PKS Base and Extension(s)
SCRIPT_LIB  := ctrmap/resources/scripting/cm_ide/sdk/EV_GEN_V/SDK5-BW-Generated.lib
EXT_LIB     := $(data_dir)/scripting/lib
EXT_SRC     := $(EXT_LIB)/src
EXT_HEAD    := $(shell find $(EXT_SRC) -name "*.h")
PKS_INCLUDE := $(EXT_SRC) $(build_dir)/.temp.lib

# Build rules

data: unpack BUILD_FIELD_EVENT_ARC BUILD_TEXT_SYSTEM_ARC BUILD_TEXT_EVENTS_ARC

### Methods

define unpack_narc
	@ echo "[<] Unpacking $(1)..."
	@ $(vpython) $(narc_tool) $(1)
endef
define pack_narc
	@ echo "[>] Packing $(1)..."
	@ $(vpython) $(narc_tool) $(1)
endef

### Recipes

# Field Script ARC
## Builds the ARC.
BUILD_FIELD_EVENT_ARC: $(venv)
	@ $(call unpack_narc, $(FIELD_EVENT_ARC))
	@ $(MAKE) BUILD_FIELD_EVENT
	@ $(call pack_narc, $(FIELD_EVENT_ARC))
## Builds the files in the ARC.
BUILD_FIELD_EVENT: $(FIELD_SCRIPTS)
$(FIELD_EVENT_ARC)/%: $(FIELD_EVENT_ROOT)/%.pks $(EXT_HEAD)
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(dir $@)
	@ mkdir -p $(log_dir)
	@ # Pre-process PKS file
	@ $(python) $(pks_preproc) $(addprefix -i, $(dir $(hdrs))) -p $< -o $(build_dir)/.temp.$(notdir $<)
	@ # Extract script command database
	@ unzip -p $(CTRMapV) $(SCRIPT_LIB) > $(build_dir)/.temp.lib
	@ # Compile
	@ logfile="$(log_dir)/$(basename $(notdir $<))"; \
	  $(java) -cp $(CTRMap) ctrmap.pokescript.LangCompiler -t ntrv -i $(build_dir)/.temp.$(notdir $<) -o $@ -I $(PKS_INCLUDE) -l $$logfile.log > $$logfile.out
	@ # Clean up
	@ rm -f $(build_dir)/.temp.lib $(build_dir)/.temp.$(notdir $<)

# Text System ARC
## Builds the ARC.
BUILD_TEXT_SYSTEM_ARC: $(venv)
	@ $(call unpack_narc, $(TEXT_SYSTEM_ARC))
	@ $(MAKE) BUILD_TEXT_SYSTEM
	@ $(call pack_narc, $(TEXT_SYSTEM_ARC))
## Builds the files in the ARC.
BUILD_TEXT_SYSTEM: $(TEXT_SYSTEM_FILES)
$(TEXT_SYSTEM_ARC)/%: $(TEXT_SYSTEM_ROOT)/%.txt
	@ echo "[+] Encoding $^..."
	@ mkdir -p $(dir $@)
	@ java -cp $(CTRMapV):$(CTRMap) ctrmap.util.tools.TextUtil -t bin -a system -i $^ -o $@

# Text Events ARC
## Builds the ARC.
BUILD_TEXT_EVENTS_ARC: $(venv)
	@ $(call unpack_narc, $(TEXT_EVENTS_ARC))
	@ $(MAKE) BUILD_TEXT_EVENTS
	@ $(call pack_narc, $(TEXT_EVENTS_ARC))
## Builds the files in the ARC.
BUILD_TEXT_EVENTS: $(TEXT_EVENTS_FILES)
$(TEXT_EVENTS_ARC)/%: $(TEXT_EVENTS_ROOT)/%.txt
	@ echo "[+] Encoding $^..."
	@ mkdir -p $(dir $@)
	@ java -cp $(CTRMapV):$(CTRMap) ctrmap.util.tools.TextUtil -t bin -a script -i $^ -o $@
