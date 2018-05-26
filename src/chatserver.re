let server = Protobufs.Server.make();

Protobufs.Server.serverBind(
  server,
  "127.0.0.1:12345",
  Protobufs.Server.createInsecure(),
);

Protobufs.addServices(
  server,
  {
    chatService:
      Some(Protobufs.Chat.ChatService.t(~sendMessage=message => {
        Js.log2("someone invoked sendMessage:", message);
        /* Send Ack */
        ();
      })),
  },
);

Protobufs.Server.start(server);
