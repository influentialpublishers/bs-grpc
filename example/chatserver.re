let lastMessage = ref("out of the silent planet comes a message");
let server =
  Grpc.createServer(
    "127.0.0.1:12345",
    Grpc.Server.createInsecure(),
    {
      chatService:
        Some(
          Grpc.Chat.ChatService.t(~sendMessage=(call, callback) => {
            let request = call
              |> Grpc.Chat.ChatService.SendMessageRpc.request ;
            let message = request
              |> Grpc.Chat.Message.message ;
            let replyMessage = lastMessage^;
            switch (message) {
            | None => ()
            | Some(s) => lastMessage := s
            };
            Js.log2(
              "someone invoked sendMessage:",
              message
            );
            /* Send Ack */
            let ack = Grpc.Chat.MessageAck.make(~result=Grpc.Chat.MessageAck.Message(replyMessage), ());
            Js.log2("ack=", ack);
            Js.log2("callback=", callback);
            Grpc.reply(callback, ack);
            Js.log("acked");
          }),
        ),
    },
  );
