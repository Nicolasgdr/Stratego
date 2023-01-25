#ifndef STRATEGO_ENCAP_H
#define STRATEGO_ENCAP_H
#include "QString"
#include "QByteArray"
#include "QDataStream"
#include "QIODevice"

class stratego_encap
{   
    QString data_;
    QByteArray data_encapsulated;


public:
    stratego_encap()=default;
    void pack_data();
    void unpack_data();
    void set_data_encap(QByteArray);
    void set_data(QString data);
    inline QByteArray get_data_encapsulated(){return data_encapsulated;}
    inline QString get_data(){return data_;}
    void clear();
};

#endif // STRATEGO_ENCAP_H
