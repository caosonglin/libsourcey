///
//
// LibSourcey
// Copyright (c) 2005, Sourcey <http://sourcey.com>
//
// SPDX-License-Identifier:	LGPL-2.1+
//
/// @addtogroup socketio
/// @{


#ifndef SCY_SocketIO_Packet_H
#define SCY_SocketIO_Packet_H


#include "scy/json/json.h"
#include "scy/packet.h"


namespace scy {
namespace sockio {


class Packet : public IPacket
{
public:
    enum class Frame : int
    {
        Open = 0,
        Close = 1,
        Ping = 2,
        Pong = 3,
        Message = 4,
        Upgrade = 5,
        Noop = 6,
        Unknown = -1
    };

    enum class Type : int
    {
        TypeMin = 0,
        Connect = 0,
        Disconnect = 1,
        Event = 2,
        Ack = 3,
        Error = 4,
        BinaryEvent = 5,
        BinaryAck = 6,
        TypeMax = 6,
        Unknown = -1
    };

    /// Default contructor
    Packet(Frame frame = Frame::Message, Type type = Type::Event, int id = -1,
           const std::string& nsp = "/", const std::string& event = "",
           const std::string& message = "", bool ack = false);

    /// General contructor
    Packet(Type type, const std::string& message = "", bool ack = false);

    /// Message contructor
    Packet(const std::string& message, bool ack = false);

    /// JSON contructor
    Packet(const json::Value& message, bool ack = false);

    /// Event contructor
    Packet(const std::string& event, const std::string& message,
           bool ack = false);

    /// Event JSON contructor
    Packet(const std::string& event, const json::Value& message,
           bool ack = false);

    Packet(const Packet& r);
    Packet& operator=(const Packet& r);
    virtual ~Packet();

    virtual IPacket* clone() const;

    Frame frame() const;
    Type type() const;
    int id() const;
    std::string nsp() const;
    std::string message() const;
    json::Value json() const;

    void setID(int id);
    void setNamespace(const std::string& nsp);
    void setMessage(const std::string& message);
    void setAck(bool flag);

    std::size_t read(const ConstBuffer& buf);
    void write(Buffer& buf) const;

    virtual std::size_t size() const;

    bool valid() const;

    std::string frameString() const;
    std::string typeString() const;
    std::string toString() const;
    void print(std::ostream& os) const;

    virtual const char* className() const { return "SocketIO::Packet"; }

protected:
    Frame _frame;
    Type _type;
    int _id;
    std::string _nsp;
    std::string _event;
    std::string _message;
    bool _ack;
    std::size_t _size;
};


} // namespace sockio
} // namespace scy


#endif // SCY_SocketIO_Packet_H


/// @\}
