# R-TYPE Game Netcode Protocol Specification

## Table of Contents
1. [Status of this Memo](#status-of-this-memo)
2. [Copyright Notice](#copyright-notice)
3. [Abstract](#abstract)
4. [Introduction](#introduction)
    1. [Requirements Terminology](#requirements-terminology)
5. [Netcode Protocol Overview](#netcode-protocol-overview)
    1. [Connection Initiation](#connection-initiation)
    2. [Connection Closure](#connection-closure)
6. [Packet Structure](#packet-structure)
    1. [Header](#header)
    2. [Body](#body)
    3. [Action Codes and Arguments](#action-codes-and-arguments)
7. [Transmission Algorithms](#transmission-algorithms)
    1. [Packet Loss Detection](#packet-loss-detection)
    2. [Packet Loss Resolution](#packet-loss-resolution)
    3. [Sequence and Acknowledgment Management](#sequence-and-acknowledgment-management)
    4. [Handling Out-of-Order Packets](#handling-out-of-order-packets)
8. [Security Considerations](#security-considerations)
    1. [Data Encryption](#data-encryption)
    2. [Authentication](#authentication)
    3. [Data Integrity](#data-integrity)
    4. [Denial of Service Protection](#denial-of-service-protection)
    5. [Logging and Monitoring](#logging-and-monitoring)
    6. [Future Updates](#future-updates)
9. [Performance Metrics](#performance-metrics)
10. [Author's Address](#authors-address)

---

## Status of this Memo

This memo provides guidelines and information for the gaming community building R-TYPE-like games. It does not specify an Internet standard of any kind. Distribution of this memo is unlimited.

## Copyright Notice

Copyright (C) THCB Company (2023). All Rights Reserved.

## Abstract

This memo describes how to secure R-TYPE game connections over the Internet using a custom netcode protocol with binary packets. This document aims to provide high performance and synchronization between clients and servers.

---

## 1. Introduction

### 1.1. Requirements Terminology

- **MUST**: This word means that the item is an absolute requirement.
- **SHOULD**: This means the item is strongly recommended but not required.

---

## 2. Netcode Protocol Overview

### 2. Netcode Protocol Overview

#### 2.1. Connection Initiation

Upon establishing a connection, the client will send a packet with the `INIT_CONNECT` action to introduce itself to the server.

| Action       | ID            | Args |
|--------------|---------------|------|
| INIT_CONNECT | None          | None |

The server will respond with a `CREATE_USER` action, with entity ID that is the client id. This ensures that both sides use the same entity ID for the session.

| Action      | ID            | Args            |
|-------------|---------------|-----------------|
| CREATE_USER | Client ID     | Assigned Entity ID|

#### 2.2. Connection Closure

##### 2.2.1. Server-side Timeout

If the client takes more than 30 seconds without sending an `IAMALIVE` action, and no other packets are being transmitted to the server, the server will take the initiative to disconnect the client. All other clients will be informed through a `USER_DISCONNECTED` action.

| Action           | Args            |
|------------------|-----------------|
| USER_DISCONNECTED| Disconnected ID |

##### 2.2.2. Client-side Disconnection

The client can also request its disconnection by sending a `REQUEST_DISCONNECT` action to the server.

| Action            | Args |
|-------------------|------|
| REQUEST_DISCONNECT| None |

The server will confirm the disconnection with a `USER_DISCONNECTED` action, informing all other clients.

| Action           | Args            |
|------------------|-----------------|
| USER_DISCONNECTED| Disconnected ID |

#### 2.3. Client Ready Signal

Once the client is successfully connected and is ready to receive game data, it should send a `USER_READY` action to the server, along with its chosen username or pseudo.

| Action      | Args       |
|-------------|------------|
| USER_READY  | Username   |

---

## 3. Packet Structure

### 3.1. Header

The header contains metadata that describe the characteristics of the packet. Below is the updated layout of the header.

| Field                        | Size (Bytes) | Description                                        |
| ---------------------------- | ------------ | -------------------------------------------------- |
| Sequence Number              | 4            | A unique identifier for this packet.               |
| Ack Sequence Number          | 4            | The sequence number of the last packet received.   |
| Ack Mask                     | 2            | Bitmask for the last 16 received packets.          |
| Packet Size                  | 2            | Size of the Body.                                  |

#### Sequence Number

A 4-byte field that uniquely identifies this packet.

#### Ack Sequence Number

A 4-byte field that indicates the sequence number of the last packet successfully received from the other end.

#### Ack Mask

A 2-byte field representing a bitmask that gives the status of the last 16 packets received, relative to the `Ack Sequence Number`.

#### Packet Size

A 2-byte field that specifies the size of the Body.

### 3.2. Body

The body contains the data payload and the relevant metadata. Below is the layout of the body.

| Field        | Size (Bytes) | Description                                                         |
| ------------ | ------------ | ------------------------------------------------------------------- |
| Action       | 1            | Describes the type of action (e.g., move, shoot, etc.).             |
| Num IDs      | 2            | The number of IDs affected by this action.                          |
| IDs          | Variable     | The IDs affected by this action.                                    |
| Num Args     | 1            | The number of arguments related to the action.                      |
| Size Arg     | 1            | Indicates the size/type of each argument.                           |
| Arguments    | Variable     | The arguments themselves (e.g., coordinates, velocities, etc.).     |

#### Action

A 1-byte field to indicate what type of action is being sent (move, shoot, etc.).

#### Num IDs

A 1-byte value representing how many IDs are concerned by this action.

#### IDs

A list of IDs involved in the action. The size is variable and depends on `Num IDs`.

#### Num Args

A 1-byte value indicating the number of arguments related to the action. This is particularly useful for managing string arguments.

#### Size Arg

A 1-byte value used to indicate the size/type of each argument. The mapping from byte values to types is as follows:

| Byte  | Type      |
| ----- | --------- |
| 0x01  | Long      |
| 0x02  | Float     |
| 0x03  | Double    |
| 0x04  | Integer   |
| 0x05  | Short     |
| 0x06  | Byte      |
| ...   | ...       |

#### Arguments

The actual data arguments related to the action. The size and type are determined by `Num Args` and `Size Arg`, respectively.


### 3.3. Action Codes and Arguments

This section outlines the list of possible actions that can be included in a packet. Each action has a specific byte associated with it and may require various types of arguments. In case the action code is not recognized by the server or client, the packet will be ignored. Similarly, if the ID doesn't exist or the packet is malformed, the packet will also be disregarded.

#### Action Code Table

| Action Name | Byte Value | Argument Type(s)       |
|-------------|------------|------------------------|
| MOVE_LEFT   | `0x01`     | float (distance)       |
| MOVE_RIGHT  | `0x02`     | float (distance)       |
| SHOOT       | `0x03`     | None                   |
| PLAYER_DIE  | `0x04`     | None                   |
| ENEMY_SPAWN | `0x05`     | int (enemy_type)       |
| POWER_UP    | `0x06`     | int (power_up_type)    |
| ...         | ...        | ...                    |

---

## 4. Transmission Algorithms

### 4.1. Packet Loss Detection

The `AckMask` and the last received sequence number `Ack Sequence Number` are used to identify which packets have arrived successfully and which haven't. This allows both the server and the client to determine if there has been packet loss.

### 4.2. Packet Loss Resolution

A receive buffer is utilized to store packets that arrive out-of-order or are delayed. This allows for reordering and processing when the missing packets finally arrive.

### 4.3. Sequence and Acknowledgment Management

Upon receiving a new packet, both the `AckMask` and `Ack Sequence Number` are updated. This ensures that both parties are aware of which packets have been received and acknowledged.

### 4.4. Handling Out-of-Order Packets

A receive buffer is used to temporarily store packets that arrive out of their intended sequence. An algorithm updates the `AckMask` and the last received sequence number to ensure that out-of-order packets are correctly processed and acknowledged.

---

## 5. Security Considerations

As of the current version, this protocol does not include any built-in security measures. Therefore, it is recommended to use this protocol within a secure environment or overlay it with a secure transport layer.

### 5.1. Data Encryption

It's highly advisable to implement encryption algorithms to secure the data being sent. Transport Layer Security (TLS) or a similar secure protocol should be considered.

### 5.2. Authentication

Both the client and the server should be authenticated to prevent unauthorized access. A simple shared-key authentication could be used as a minimum requirement.

### 5.3. Data Integrity

Checksums or cryptographic hashes should be used to verify the integrity of the data packets, ensuring that they have not been tampered with during transit.

### 5.4. Denial of Service Protection

Rate-limiting and other anti-flooding mechanisms should be in place to prevent denial-of-service attacks.

### 5.5. Logging and Monitoring

Continuous logging and monitoring are crucial for identifying and mitigating security threats in real-time.

### 5.6. Future Updates

It is recommended to plan for future versions of the protocol that will include robust security features.

---

## 6. Performance Metrics

Metrics such as latency and bandwidth should be considered here.

---

## 7. Author's Address

Clément LAGASSE - clement.lagasse@epitech.eu
