#include "../../headers/history.h"
#include "../dbHandlers/db_handlers.h"

History::History() {
    this->parcels_number = read_parcels_number();
    this->parcels_history = read_parcels();
}

