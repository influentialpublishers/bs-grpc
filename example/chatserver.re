let lastMessage = ref("out of the silent planet comes a message");
let credentials = Grpc.Server.Credentials.Insecure.make();
let chatService =
  Grpc.Chat.ChatService.t(~sendMessage=(call, callback) => {
    let request = call |> Grpc.Chat.ChatService.SendMessageRpc.request;
    let message = request |> Grpc.Chat.Message.message;
    let replyMessage = lastMessage^;
    switch (message) {
    | None => ()
    | Some(s) => lastMessage := s
    };
    /* Send Ack */
    let ack =
      Grpc.Chat.MessageAck.make(
        ~result=Grpc.Chat.MessageAck.Message(replyMessage),
        (),
      );
    Grpc.reply(callback, ack);
  });

let server = Grpc.Server.make("127.0.0.1:12345", ~credentials, ~chatService);
