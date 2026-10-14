project_data = $(unpack_dir)/data

# Command definitions
java = java

# Tool definitions
CTRMap  = $(tools_dir)/CTRMap.jar
CTRMapV = $(tools_dir)/CTRMapV.jar

# Black1Playground data
playground_dir = $(project_data)/Black1Playground

# ARC Definitions
FIELD_EVENT_ARC = $(project_data)/a/0/5/7

# Data Definitions
FIELD_EVENT_ROOT = $(data_dir)/scripting/scripts

# Targets
FIELD_SCRIPTS := $(patsubst $(FIELD_EVENT_ROOT)/%.pks, $(playground_dir)/%.ev, $(wildcard $(FIELD_EVENT_ROOT)/*))

# PKS Base and Extension(s)
SCRIPT_LIB  := ctrmap/resources/scripting/cm_ide/sdk/EV_GEN_V/SDK5-B2W2-Generated.lib
EXT_LIB     := $(data_dir)/scripting/lib
EXT_SRC     := $(EXT_LIB)/src
EXT_HEAD    := $(shell find $(EXT_SRC) -name "*.h")
PKS_INCLUDE := $(EXT_SRC) $(build_dir)/.temp.lib

# Build rules

data: $(FIELD_SCRIPTS)

# Field Script ARC
## Builds the files in the ARC.
$(playground_dir)/%.ev: $(FIELD_EVENT_ROOT)/%.pks $(EXT_HEAD)
	@ echo "[+] Compiling $<..."
	@ mkdir -p $(dir $@)
	@ unzip -p $(CTRMapV) $(SCRIPT_LIB) > $(build_dir)/.temp.lib
	@ logfile="$(build_dir)/$(basename $(notdir $<))"; \
	  $(java) -cp $(CTRMap) ctrmap.pokescript.LangCompiler -t ntrv -i $< -o $@ -I $(PKS_INCLUDE) -l $$logfile.log > $$logfile.out
	@ rm -f $(build_dir)/.temp.lib
