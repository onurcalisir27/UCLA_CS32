
void removeBad(vector<Restaurant*>& v)
{
	for (vector<Restaurant*>::iterator p = v.begin(); p != v.end();)
	{
	    Restaurant* r = *p;
		if (r->stars() <= 2)
		{
			p = v.erase(p);
			delete r;
		}
		else
		{
			p++;
		}
	}
}
