const grpc = require('@grpc/grpc-js');
const protoLoader = require('grpc-alt-proto-loader')
const path = require('path')

const protoLoaderOptions = {
  oneofs: true,
  defaults: false,
  keepCase: true,
  includeDirs: [
    '.',
    path.resolve(__dirname, '..'),
  ]
}

module.exports.load = (filename) => {
  protoLoaderOptions.includeDirs.push(path.dirname(filename));
  const protoLoaderResult = protoLoader.loadSync(filename, protoLoaderOptions)
  const grpcObject = grpc.loadPackageDefinition(protoLoaderResult.packageDefinition)
  protoLoader.addTypesToGrpcObject(grpcObject, protoLoaderResult.messageTypes)
  return grpcObject
}
