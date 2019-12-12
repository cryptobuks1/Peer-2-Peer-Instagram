#include "../headers/Message.h"
#include "../headers/utils.h"

Message::Message(): message_type(Request), operation(0), packet_index(0), total_packets(0), message_size(0), message(""), request_id(""), IP(""),image_id(0) {

}


Message::Message(requestInfo req_info){
    message = req_info.p_message;
    message_size = req_info.p_message.length()+1;
    operation = req_info.operation;
    packet_index = req_info.packet_index;
    total_packets = 0;
    message_type = req_info.msg_type;
    // resource attributes
    image_id = req_info.image_id;
    request_id = req_info.request_id;
    IP = req_info.IP;
    port = req_info.port;
}

Message::Message(std::string & marshalled_base64){
    std::string decoded = decode64(marshalled_base64);
    deserialize(decoded);
}

// PRIVATE
void Message::deserialize(std::string decoded){

    std::string msg_decoded;
    message_type  = static_cast<MessageType>(decoded[0] - '0');
    message_size  = hex_to_int(decoded.substr(3, 16));
    operation = hex_to_int(decoded.substr(21, 8 ));
    packet_index = hex_to_int(decoded.substr(31, 8 ));
    image_id = hex_to_int(decoded.substr(41, 8 ));
    total_packets = hex_to_int(decoded.substr(51, 8));
    port = hex_to_int(decoded.substr(61, 8));
    request_id = decoded.substr( 69, decoded.substr(69).find(";"));
    IP = decoded.substr(69+request_id.length()+1, decoded.substr(69+request_id.length()+1).find(";") );
    sender_name = decoded.substr(69+request_id.length()+2+IP.length(), decoded.substr(69+request_id.length()+2+IP.length(),69+IP.length()+request_id.length()+2).find(";"));
    msg_decoded = decoded.substr(69+request_id.length()+3+IP.length() + sender_name.length());
    message = msg_decoded;

}

std::string Message::serialize(){
    // convert attributes to string
    std::string mtype = std::to_string(int(message_type));
    std::string size_str = int_to_hex(message_size);

    std::string op_str = int_to_hex(operation);
    std::string packet_index_str = int_to_hex(packet_index);
    std::string tot_packets_str = int_to_hex(total_packets);

    std::string img_id = int_to_hex(image_id);
    std::string port_str = int_to_hex(port);

    // type: 1 byte | size: 2 bytes + 16 bytes  | operation : 2 bytes + 16 bytes
    // | rpc_id : 2 bytes + 16 bytes | img_id: 2 bytes + 8 bytes | storage_location | message

    std::string to_encode = mtype + size_str + op_str + packet_index_str + img_id + tot_packets_str + port_str + request_id + ";" + IP + ";" + sender_name + ";" + message;
    return to_encode;
}


std::string Message::marshal(){
    std::string to_encode = serialize();
    std::string encoded = encode64(to_encode);
    return encoded;
}
// getters
std::string Message::getMessage(){
    return message;
}
size_t Message::getMessageSize(){
    return message_size;
}
MessageType Message::getMessageType(){
    return message_type;
}
int Message::getOperation(){
    return operation;
}
int Message::getPacketIndex(){
    return packet_index;
}
int Message::getTotalPackets(){
    return total_packets;
}

std::string Message::getSenderName(){
    return sender_name;
}

void Message::setSenderName(std::string name) {
    sender_name = name;
}


// setters
void Message::setMessage (std::string message, size_t message_size){
    this->message = message;
    this->message_size = message_size;
}
void Message::setMessageSize(size_t message_size){
    this->message_size = message_size;
}
void Message::setMessageType (MessageType message_type){
    this->message_type = message_type;
}
void Message::setOperation(int operation){
    this->operation = operation;
}

void Message::setPacketIndex(int packet_index){
    this->packet_index = packet_index;
}
void Message::setTotalPacket(int total_packets){
    this->total_packets = total_packets;
}
void Message::setRequestId(std::string request_id){
    this->request_id = request_id;
}
void Message::setIP (std::string ip){
    this->IP = ip;
}
void Message::setPort(int port){
    this->port = port;
}
int Message::getImageId(){
    return image_id;
}
int Message::getPort() {
    return port;
}
std::string Message::getRequestId(){
    return request_id;
}
std::string Message::getIP(){
    return IP;
}

Message Message::buildAckMsg(Message & m){
    Message ack_msg  = Message();
    ack_msg.setMessageType(ACK);
    ack_msg.setRequestId(m.getRequestId());
    ack_msg.setPacketIndex(m.getPacketIndex());
    ack_msg.setTotalPacket(m.getTotalPackets());
    ack_msg.setIP(m.getIP());
    ack_msg.setPort(m.getPort());
    return ack_msg;
}

Message::~Message(){

}

std::ostream& operator<< (std::ostream& stream, const Message& msg) {
    stream << "Type: " << msg.message_type
           << ", Size: " << msg.message_size
           << ", Operation: " << msg.operation
           << ", Packet Index: " << msg.packet_index
           << ", Total Packets: " << msg.total_packets
           << ", Message: " << msg.message
           << ", Image ID: " << msg.image_id
           << ", Sender IP: " << msg.IP
           << ", Sender Port " << msg.port
           << ", Request ID: " << msg.request_id << std::endl;
    return stream;
}