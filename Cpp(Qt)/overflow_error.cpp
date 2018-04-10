#include "overflow_error.h"


overflow_error::overflow_error() {
}

const char* overflow_error::what() const throw()
{
    return "Intero selezionato non permesso";
}
