#define OK false

bool do_something(int)
{
}

bool init_stuff(int)
{
}

bool prepare_stuff(int)
{
}

bool do_the_thing(int)
{
}

bool undo_something()
{
}

bool uninit_stuff()
{
}

bool unprepare_stuff()
{
}

bool foo(int bar)
{
    bool return_value = OK;
    bool something_done = !OK;
    bool stuff_inited = !OK;
    bool stuff_prepared = !OK;

    // Prepare
    				    { return_value = do_something(bar); 	something_done = return_value; 	}
    if (return_value == OK) { return_value = init_stuff(bar); 	stuff_inited = return_value;		}
    if (return_value == OK) { return_value = prepare_stuff(bar);	stuff_prepared = return_value;	}

    // Do the thing
    if (return_value == OK) { return_value = do_the_thing(bar); }

    // Clean up only when there is an error
    if (return_value != OK && stuff_prepared == OK)	{ unprepare_stuff();}
    if (return_value != OK && stuff_inited == OK)	{ uninit_stuff();	  }
    if (return_value != OK && something_done == OK)	{ undo_something(); }

    // Cleanup always
    // if (stuff_prepared == OK) 	{ unprepare_stuff(); 	}
    // if (stuff_inited == OK) 	{ uninit_stuff();		}
    // if (something_done == OK)	{ undo_something();	}

    return return_value;
}