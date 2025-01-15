
void listAll(const MenuItem* m, string path) // two-parameter overload
{
    
  if (m->menuItems() == nullptr || m->menuItems()->size() == 0) 
      return;
  
  for (vector<MenuItem*>::const_iterator p = m->menuItems()->begin(); p != m->menuItems()->end(); p++)
  {
      cout << path << (*p)->name() << endl;
      listAll(*p, path + (*p)->name() + "/");
  }

}
