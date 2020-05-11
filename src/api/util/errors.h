#ifndef ERRORS_DEFINITION
#define ERRORS_DEFINITION

#define BADFILE_ERROR -1
#define BADFILEEXTENSION_ERROR -2
#define BADARGUMENTS_ERROR -3
#define BADCODIFICATION_ERROR -4
#define UNDEFINEDVARIABLE_ERROR -5
#define UNSUPPORTEDFUNC_ERROR -6
#define SOLVING_ERROR -7


namespace smtapierrors{

void fatalError(std::string message, int errorCode);
void warning(std::string message);

}

#endif

