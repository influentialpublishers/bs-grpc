const grpc = require('grpc')
const protoLoader = require('grpc-alt-proto-loader')
const path = require('path')
const resolve = require('resolve')

const protoLoaderOptions = {
  oneofs: true,
  defaults: false,
  keepCase: true,
  includeDirs: [
    '.',
    path.resolve(__dirname, '..'),
    path.resolve(path.dirname(resolve.sync('grpc-tools', { basedir: '.' })), 'bin'),
  ]
}

/* Emulate require('grpc') */
for (let k in grpc)
  module.exports[k] = grpc[k]

module.exports.load = filename => {
  const protoLoaderResult = protoLoader.loadSync(filename, protoLoaderOptions)
  const grpcObject = grpc.loadPackageDefinition(protoLoaderResult.packageDefinition)
  protoLoader.addTypesToGrpcObject(grpcObject, protoLoaderResult.messageTypes)
  return grpcObject
}
