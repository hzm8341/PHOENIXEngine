// PX2AIAgent.inl

//----------------------------------------------------------------------------
inline btRigidBody* AIAgent::GetRigidBody()
{
	return rigidBody_;
}
//----------------------------------------------------------------------------
inline AIAgentWorld *AIAgent::GetAgentWorld()
{
	return mAgentWorld;
}
//----------------------------------------------------------------------------
inline float AIAgent::GetHealth() const
{
	return health_;
}
//----------------------------------------------------------------------------
inline float AIAgent::GetHeight() const
{
	return height_;
}
//----------------------------------------------------------------------------
inline float AIAgent::GetRadius() const
{
	return radius_;
}
//----------------------------------------------------------------------------