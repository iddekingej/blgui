#ifndef __STRINGLINEITERATOR_H_
#define  __STRINGLINEITERATOR_H_
#include <QString>

/**
 * A java style text line iterator
 * 
 * A text contains multiple lines (each line separated by a lf)
 * This class iterates through the text line by line
 */
class TStringLineIterator{
private:
/**
 *  Text to iterate  line by line (lines are separated by a lf)
 */
	QString text;
	
/**
 *  Current position inside text.
 *  Starts with pos=0,
 *  When pos=-1 the end is reached.
 */
	int pos=0;
public:

/**
 * Initialize the iterator
 * 
 * \param p_text This text will be iterated
 */

	inline TStringLineIterator(const QString &p_text){ 
		text=p_text;
	}

/**
 * Get the next line from the text and 
 * set the current position to the next line
 * 
 * \return current line.
 */	
	
	inline QStringRef next(){		
		int l_newPos=text.indexOf("\n",pos);
		QStringRef l_return;
		if(l_newPos>=0){
			l_return=text.midRef(pos,l_newPos-pos);
			pos=l_newPos+1;
		} else {
			l_return=text.midRef(pos);
			pos=l_newPos;
		}
			
		return l_return;
	}
	
/**
 *  Checks if there are more lines to iterate
 * 
 *  \return  True  - There are more lines
 *           False - End of the text is reached
 */
	bool hasNext(){
		return pos!= -1;
	}
	
};

#endif
