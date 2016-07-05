#!/bin/bash
#
# qb50-cfe.launch.sh
#
# Generates the qb50-cfe.launch XML configuration,
# supplants the IP address of the current host machine
# for the variable $IP and outputs the generated file
# to qb50-cfe.launch.
#

IP=$(ip addr show dev eth1 | grep -o 'inet [0-9.]*' | cut -d' ' -f2)

cat - <<EOF> qb50-cfe.launch
<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<launchConfiguration type="org.eclipse.cdt.launch.remoteApplicationLaunchType">
  <booleanAttribute key="org.eclipse.cdt.dsf.gdb.AUTO_SOLIB" value="true"/>
  <listAttribute key="org.eclipse.cdt.dsf.gdb.AUTO_SOLIB_LIST"/>
  <stringAttribute key="org.eclipse.cdt.dsf.gdb.DEBUG_NAME" value="arm-unknown-linux-gnueabi-gdb"/>
  <booleanAttribute key="org.eclipse.cdt.dsf.gdb.DEBUG_ON_FORK" value="false"/>
  <stringAttribute key="org.eclipse.cdt.dsf.gdb.GDB_INIT" value=".gdbinit"/>
  <booleanAttribute key="org.eclipse.cdt.dsf.gdb.NON_STOP" value="false"/>
  <booleanAttribute key="org.eclipse.cdt.dsf.gdb.REVERSE" value="false"/>
  <listAttribute key="org.eclipse.cdt.dsf.gdb.SOLIB_PATH"/>
  <stringAttribute key="org.eclipse.cdt.dsf.gdb.TRACEPOINT_MODE" value="TP_NORMAL_ONLY"/>
  <booleanAttribute key="org.eclipse.cdt.dsf.gdb.UPDATE_THREADLIST_ON_SUSPEND" value="false"/>
  <intAttribute key="org.eclipse.cdt.launch.ATTR_BUILD_BEFORE_LAUNCH_ATTR" value="2"/>
  <stringAttribute key="org.eclipse.cdt.launch.COREFILE_PATH" value=""/>
  <stringAttribute key="org.eclipse.cdt.launch.DEBUGGER_ID" value="gdbserver"/>
  <stringAttribute key="org.eclipse.cdt.launch.DEBUGGER_START_MODE" value="remote"/>
  <booleanAttribute key="org.eclipse.cdt.launch.DEBUGGER_STOP_AT_MAIN" value="true"/>
  <stringAttribute key="org.eclipse.cdt.launch.DEBUGGER_STOP_AT_MAIN_SYMBOL" value="main"/>
  <stringAttribute key="org.eclipse.cdt.launch.PROGRAM_NAME" value="bin/core-linux.bin"/>
  <stringAttribute key="org.eclipse.cdt.launch.PROJECT_ATTR" value="qb50-cfe"/>
  <booleanAttribute key="org.eclipse.cdt.launch.PROJECT_BUILD_CONFIG_AUTO_ATTR" value="false"/>
  <stringAttribute key="org.eclipse.cdt.launch.PROJECT_BUILD_CONFIG_ID_ATTR" value=""/>
  <booleanAttribute key="org.eclipse.cdt.launch.remote.RemoteCDSFDebuggerTab.DEFAULTS_SET" value="true"/>
  <stringAttribute key="org.eclipse.debug.core.ATTR_GDBSERVER_COMMAND" value="gdbserver"/>
  <stringAttribute key="org.eclipse.debug.core.ATTR_GDBSERVER_PORT" value="2345"/>
  <stringAttribute key="org.eclipse.debug.core.ATTR_PRERUN_CMDS" value="rm -fr /root/cfe; scp -r vagrant@$IP:/home/vagrant/workspace/qb50-cfe/bin /root/cfe; cd /root/cfe"/>
  <booleanAttribute key="org.eclipse.debug.core.ATTR_SKIP_DOWNLOAD_TO_TARGET" value="false"/>
  <stringAttribute key="org.eclipse.debug.core.ATTR_TARGET_PATH" value="/root/cfe/core-linux.bin"/>
  <listAttribute key="org.eclipse.debug.core.MAPPED_RESOURCE_PATHS">
    <listEntry value="/qb50-cfe"/>
  </listAttribute>
  <listAttribute key="org.eclipse.debug.core.MAPPED_RESOURCE_TYPES">
    <listEntry value="4"/>
  </listAttribute>
  <stringAttribute key="org.eclipse.debug.core.REMOTE_TCP" value="$BOARD_IP"/>
</launchConfiguration>
EOF
