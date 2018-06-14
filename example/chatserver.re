let lastMessage = ref("out of the silent planet comes a message");
let server =
  Protobufs.createServer(
    "127.0.0.1:12345",
    Protobufs.Server.createInsecure(),
    {
      chatService:
        Some(
          Protobufs.Chat.ChatService.t(~sendMessage=(call, callback) => {
            let request = call
              |> Protobufs.Chat.ChatService.SendMessageRpc.request ;
            let message = request
              |> Protobufs.Chat.Message.message ;
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
            let ack = Protobufs.Chat.MessageAck.make(~result=Protobufs.Chat.MessageAck.Message(replyMessage), ());
            Js.log2("ack=", ack);
            Js.log2("callback=", callback);
            callback(.
              Js.Nullable.null,
              ack,
              Js.Nullable.undefined,
              Js.Nullable.undefined,
            );
            Js.log("acked");
          }),
        ),
    },
  );
