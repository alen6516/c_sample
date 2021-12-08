when init_logger()
one can specify a local logger by caller's module

in _log()
one can parse the filename and get the module and see if there is local logger

a global logger, may run on an independent thread, and has a global file to write
caller use DEBUG, INFO, ERROR to write log
each caller can register a module name, and a independent file to write
caller use queue to hand over the log job to logger
