#include "stratego_encap.h"

void stratego_encap::pack_data(){
    QDataStream in(&this->data_encapsulated,QIODevice::ReadWrite);
    in<<data_;

}

void stratego_encap::unpack_data(){
    QDataStream in(&this->data_encapsulated,QIODevice::ReadWrite);
    in<<data_;

}

void stratego_encap::set_data_encap(QByteArray array){
    this->data_encapsulated = std::move(array);
}

void stratego_encap::set_data(QString data){
     this->data_=std::move(data);
}

void stratego_encap::clear(){
    data_.clear();
    data_encapsulated.clear();
}
