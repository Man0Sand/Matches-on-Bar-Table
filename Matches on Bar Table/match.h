#ifndef MATCH_H
#define MATCH_H

class cl_match
{
public:
	cl_match() : m_removed(false) {}
	void remove(){ m_removed = true; }
	bool is_removed(){ return m_removed; }
private:
	bool m_removed;
};	

#endif // MATCH_H
