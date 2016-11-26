#ifndef __STRINGLINEITERATOR_H_
#define  __STRINGLINEITERATOR_H_
#include <QString>

class TStringLineIterator{
private: 
	QString text;
	int pos=0;
public:
	inline TStringLineIterator(QString &p_text){ 
		text=p_text;
	}
	
	inline QStringRef next(){		
		int l_newPos=text.indexOf("\n",pos);
		QStringRef l_return;
		l_return=text.midRef(pos,l_newPos-pos);
		if(l_newPos>=0){
			pos=l_newPos+1;
		} else {
			pos=l_newPos;
		}
			
		return l_return;
	}
	
	bool hasNext(){
		return pos!= -1;
	}
	
};

#endif
