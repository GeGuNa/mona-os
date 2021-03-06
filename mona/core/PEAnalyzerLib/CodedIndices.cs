// This file was generated by Code Generator.
// 2003/08/17 10:28:12

using System;

namespace Girl.PEAnalyzer
{
	public enum CodedIndices
	{
		TypeDefOrRef,
		HasConstant,
		HasCustomAttribute,
		HasFieldMarshal,
		HasDeclSecurity,
		MemberRefParent,
		HasSemantics,
		MethodDefOrRef,
		MemberForwarded,
		Implementation,
		CustomAttributeType,
		ResolutionScope
	}

	public class CodedIndex
	{
		public static MetadataTables[][] Data = new MetadataTables[][]
		{
			new MetadataTables[]
			{
				MetadataTables.TypeDef,
				MetadataTables.TypeRef,
				MetadataTables.TypeSpec
			},
			new MetadataTables[]
			{
				MetadataTables.Field,
				MetadataTables.Param,
				MetadataTables.Property
			},
			new MetadataTables[]
			{
				MetadataTables.MethodDef,
				MetadataTables.Field,
				MetadataTables.TypeRef,
				MetadataTables.TypeDef,
				MetadataTables.Param,
				MetadataTables.InterfaceImpl,
				MetadataTables.MemberRef,
				MetadataTables.Module,
				MetadataTables.DeclSecurity,
				MetadataTables.Property,
				MetadataTables.Event,
				MetadataTables.StandAloneSig,
				MetadataTables.ModuleRef,
				MetadataTables.TypeSpec,
				MetadataTables.Assembly,
				MetadataTables.AssemblyRef,
				MetadataTables.File,
				MetadataTables.ExportedType,
				MetadataTables.ManifestResource
			},
			new MetadataTables[]
			{
				MetadataTables.Field,
				MetadataTables.Param
			},
			new MetadataTables[]
			{
				MetadataTables.TypeDef,
				MetadataTables.MethodDef,
				MetadataTables.Assembly
			},
			new MetadataTables[]
			{
				MetadataTables.NotUsed,
				MetadataTables.TypeRef,
				MetadataTables.ModuleRef,
				MetadataTables.MethodDef,
				MetadataTables.TypeSpec
			},
			new MetadataTables[]
			{
				MetadataTables.Event,
				MetadataTables.Property
			},
			new MetadataTables[]
			{
				MetadataTables.MethodDef,
				MetadataTables.MemberRef
			},
			new MetadataTables[]
			{
				MetadataTables.Field,
				MetadataTables.MethodDef
			},
			new MetadataTables[]
			{
				MetadataTables.File,
				MetadataTables.AssemblyRef,
				MetadataTables.ExportedType
			},
			new MetadataTables[]
			{
				MetadataTables.NotUsed,
				MetadataTables.NotUsed,
				MetadataTables.MethodDef,
				MetadataTables.MemberRef,
				MetadataTables.NotUsed
			},
			new MetadataTables[]
			{
				MetadataTables.Module,
				MetadataTables.ModuleRef,
				MetadataTables.AssemblyRef,
				MetadataTables.TypeRef
			}
		};
	}
}
