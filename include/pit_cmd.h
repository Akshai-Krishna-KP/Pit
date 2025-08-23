/**
 * @file pit_cmd.h
 * @author Akshai krishna KP
 * @brief a header file declaring all the available pit commands
 * @version 0.1
 * @date 2025-08-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef PIT_CMD_H
#define PIT_CMD_H

// Declaration of all the commands
int cmd_start(int argc, const char **argv);
int cmd_add(int argc, const char **argv);
int cmd_commit(int argc, const char **argv);
int cmd_config(int argc, const char **argv);
int cmd_clone(int argc, const char **argv);
int cmd_status(int argc, const char **argv);
int cmd_log(int argc, const char **argv);
int cmd_branch(int argc, const char **argv);
int cmd_checkout(int argc, const char **argv);
int cmd_merge(int argc, const char **argv);
int cmd_rebase(int argc, const char **argv);
int cmd_push(int argc, const char **argv);
int cmd_pull(int argc, const char **argv);     

#endif