------------------------------------------------------------------------------
--                                                                          --
--                         GNAT COMPILER COMPONENTS                         --
--                                                                          --
--           S Y S T E M . F I N A L I Z A T I O N _ M A S T E R S          --
--                                                                          --
--                                 S p e c                                  --
--                                                                          --
--          Copyright (C) 2011-2024, Free Software Foundation, Inc.         --
--                                                                          --
-- GNAT is free software;  you can  redistribute it  and/or modify it under --
-- terms of the  GNU General Public License as published  by the Free Soft- --
-- ware  Foundation;  either version 3,  or (at your option) any later ver- --
-- sion.  GNAT is distributed in the hope that it will be useful, but WITH- --
-- OUT ANY WARRANTY;  without even the  implied warranty of MERCHANTABILITY --
-- or FITNESS FOR A PARTICULAR PURPOSE.                                     --
--                                                                          --
-- As a special exception under Section 7 of GPL version 3, you are granted --
-- additional permissions described in the GCC Runtime Library Exception,   --
-- version 3.1, as published by the Free Software Foundation.               --
--                                                                          --
-- You should have received a copy of the GNU General Public License and    --
-- a copy of the GCC Runtime Library Exception along with this program;     --
-- see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see    --
-- <http://www.gnu.org/licenses/>.                                          --
--                                                                          --
-- GNAT was originally developed  by the GNAT team at  New York University. --
-- Extensive contributions were provided by Ada Core Technologies Inc.      --
--                                                                          --
------------------------------------------------------------------------------

with Ada.Finalization;
with System.Storage_Elements;
with System.Storage_Pools;

package System.Finalization_Masters is
   pragma Preelaborate;

   --  A reference to primitive Finalize_Address. The expander generates an
   --  implementation of this procedure for each controlled and class-wide
   --  type. Since controlled objects are simply viewed as addresses once
   --  allocated through a master, Finalize_Address provides a backward
   --  indirection from an address to a type-specific context.

   type Finalize_Address_Ptr is access procedure (Obj : System.Address);

   --  Heterogeneous collection type structure

   type FM_Node is private;
   type FM_Node_Ptr is access all FM_Node;
   pragma No_Strict_Aliasing (FM_Node_Ptr);

   --  A reference to any derivation from Root_Storage_Pool. Since this type
   --  may not be used to allocate objects, its storage size is zero.

   type Any_Storage_Pool_Ptr is
     access System.Storage_Pools.Root_Storage_Pool'Class;
   for Any_Storage_Pool_Ptr'Storage_Size use 0;

   --  Finalization master type structure. A unique master is associated with
   --  each access-to-controlled or access-to-class-wide type. Masters also act
   --  as components of subpools. By default, a master contains objects of the
   --  same designated type but it may also accommodate heterogeneous objects.

   type Finalization_Master is
     new Ada.Finalization.Limited_Controlled with private;

   --  A reference to a finalization master. Since this type may not be used
   --  to allocate objects, its storage size is zero.

   type Finalization_Master_Ptr is access all Finalization_Master;
   for Finalization_Master_Ptr'Storage_Size use 0;

   procedure Attach_Unprotected
     (N                : not null FM_Node_Ptr;
      Finalize_Address : not null Finalize_Address_Ptr;
      L                : not null FM_Node_Ptr);
   --  Prepend a node to a specific finalization master

   procedure Detach_Unprotected (N : not null FM_Node_Ptr);
   --  Remove a node from an arbitrary finalization master

   overriding procedure Finalize (Master : in out Finalization_Master);
   --  Lock the master to prevent allocations during finalization. Iterate over
   --  the list of allocated controlled objects, finalizing each one by calling
   --  its specific Finalize_Address. In the end, deallocate the dummy head.

   function Finalization_Started (Master : Finalization_Master) return Boolean;
   --  Return the finalization status of a master

   function Header_Size return System.Storage_Elements.Storage_Count;
   --  Return the size of type FM_Node as Storage_Count

   function Objects (Master : Finalization_Master) return FM_Node_Ptr;
   --  Return the header of the doubly-linked list of controlled objects

   procedure Print_Master (Master : Finalization_Master);
   --  Debug routine, outputs the contents of a master

private
   --  Heterogeneous collection type structure

   type FM_Node is record
      Finalize_Address : Finalize_Address_Ptr := null;

      Prev : FM_Node_Ptr := null;
      Next : FM_Node_Ptr := null;
   end record;

   --  Finalization master type structure. A unique master is associated with
   --  each access-to-controlled or access-to-class-wide type. Masters also act
   --  as components of subpools. By default, a master contains objects of the
   --  same designated type but it may also accommodate heterogeneous objects.

   type Finalization_Master is
     new Ada.Finalization.Limited_Controlled with
   record
      Base_Pool : Any_Storage_Pool_Ptr := null;
      --  A reference to the pool which this finalization master services. This
      --  field is used in conjunction with the build-in-place machinery.

      Objects : aliased FM_Node;
      --  A doubly linked list which contains the headers of all controlled
      --  objects allocated in a [sub]pool.

      Finalization_Started : Boolean := False;
      --  A flag used to detect allocations which occur during the finalization
      --  of a master. The allocations must raise Program_Error. This scenario
      --  may arise in a multitask environment.
   end record;

   --  Since RTSfind cannot contain names of the form RE_"+", the following
   --  routine serves as a wrapper around System.Storage_Elements."+".

   function Add_Offset_To_Address
     (Addr   : System.Address;
      Offset : System.Storage_Elements.Storage_Offset) return System.Address;

   function Base_Pool
     (Master : Finalization_Master) return Any_Storage_Pool_Ptr;
   --  Return a reference to the underlying storage pool on which the master
   --  operates.

   overriding procedure Initialize (Master : in out Finalization_Master);
   --  Initialize the dummy head of a finalization master

   procedure Set_Base_Pool
     (Master   : in out Finalization_Master;
      Pool_Ptr : Any_Storage_Pool_Ptr);
   --  Set the underlying pool of a finalization master

end System.Finalization_Masters;
