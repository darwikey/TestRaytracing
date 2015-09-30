#ifndef __SINGLETONS_H__
#define __SINGLETONS_H__



template <typename T>
class Singleton
{
protected:

    // Constructeur/destructeur
    Singleton () { }
    ~Singleton () { }

public:
    // Interface publique
    static T *getInstance()
    {
        if (NULL == _singleton)
        {

            _singleton = new T;
        }

        return (static_cast<T*> (_singleton));
    }

	static bool isInit()
	{
		return _singleton!=NULL;
	}

    static void Destroy ()
    {
        if (NULL != _singleton)
        {
            delete _singleton;
            _singleton = NULL;
        }
    }

private:

    // Unique instance
    static T *_singleton;

};

template <typename T>
T *Singleton<T>::_singleton = NULL;


#endif

