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
  if (do_something(bar) != OK) goto out1;
  if (init_stuff(bar) != OK) goto out2;
  if (prepare_stuff(bar) != OK) goto out3;
  if (do_the_thing(bar) != OK) goto out4;
  
  return OK;

 // Clean up only when there is an error
 out4:	unprepare_stuff();
 out3: 	uninit_stuff();
 out2:	undo_something();
 out1:  return !OK;
}