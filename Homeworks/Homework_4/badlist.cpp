
void removeBad(list<Restaurant*>& li)
{
	for (list<Restaurant*>::iterator p = li.begin(); p != li.end();)
	{
		Restaurant* r = *p;
		if (r->stars() <= 2)
		{
			p = li.erase(p);
			delete r;
		}
		else
		{
			p ++;
		}
	}
}